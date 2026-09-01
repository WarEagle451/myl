#if 0
#pragma once
#include <myl/definitions.hpp>

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

/// MYTODO: Changes
/// - Make it so when adding an arg you can put 'a' instead of '-a'. this is important so the user doesnt mess things up
/// - Add the ability to extarct lists as arrays, vectors, etc

/// POsitional args are ones without a short or long name, maybe

/// MYTODO: fix the types choosen

/// Inputs wanted
// Long flag, --help
// short flag, -h
// long option, --output file.txt
// long option equals, --output=file.txt
// combined short flags, -abc
// short option, -o file.txt
// short option equals -o file.txt
/// positional args

/// Data types that should be supported:
/// strings,
/// ints,
/// floats,
/// doubles,
/// lists/arrays.
/// enums

/// change the type_value to something like converter, so the user can expand it if needed

/// https://github.com/FlorianRappl/CmdParser
/// https://www.dmulholl.com/docs/argspp/master/
/// https://docs.python.org/3/library/argparse.html

namespace myl {
    namespace details {
        template<typename T>
        struct type_value { /// Probs should have a diff name, or at least somewhere else
            MYL_NO_DISCARD static constexpr auto convert(const std::string& value) -> T {
                T out{};
                std::from_chars(value.c_str(), value.c_str() + value.size(), out);
                return out;
            }

            MYL_NO_DISCARD static constexpr auto default_value() noexcept -> std::string {
                return std::to_string(static_cast<T>(0));
            }
        };

        template<>
        struct type_value<bool> {
            MYL_NO_DISCARD static constexpr auto convert(const std::string& value) -> bool {
                return "1" == value || "on" == value || "true" == value || "yes" == value;
            }

            MYL_NO_DISCARD static constexpr auto default_value() noexcept -> std::string {
                return "false";
            }
        };

        template<>
        struct type_value<std::string> {
            MYL_NO_DISCARD static constexpr auto convert(const std::string& value) -> std::string {
                return value;
            }

            MYL_NO_DISCARD static constexpr auto default_value() noexcept -> std::string {
                return "";
            }
        };

        /// MYTODO: add ability to convert to an array for lists
        /// MYTODO: add ability to convert to a type that will allow an array for different types
    }

    struct command_line_option {
       std::string short_name{ "" };
       std::string long_name{ "" };
       std::string help_message{ "" };
       std::string default_value{ "" };
       myl::u8     arg_count{ 0 };
       /// bool required = false.
    };

    class command_line_parser {
        struct option_entry : command_line_option {
            MYL_NO_DISCARD constexpr option_entry(const command_line_option& option)
                : command_line_option{ option }
                , seen{ false }
                , data{ "" } {}

            bool seen;
            std::string data;
        };

        const std::string m_program_name;
        void (*m_error_callback)(const std::string&);

        std::vector<option_entry> m_options;
    public:
///        MYL_NO_DISCARD constexpr command_line_parser(const std::string& program_name, void (*error_callback)(const std::string&) = nullptr)
///            : m_program_name{ program_name }
///            , m_error_callback{ error_callback == nullptr ? &command_line_parser::default_error_callback : error_callback } {}

///        constexpr ~command_line_parser() = default;

        template<typename T>
        MYL_NO_DISCARD constexpr auto get(std::string_view option_name) const -> T {
            /// MYTODO: Figure out how to convert lists
            /// ALSO, should this support just looking for 'a' and not include the prefix '-'
            
            for (auto& entry : m_options)
                if (entry.short_name == option_name || entry.long_name == option_name)
                    return details::type_value<T>::convert(entry.seen ? entry.data : entry.default_value);
            /// THIS SHOULD NOT BE REACHABLE UNLESS THE USER HAS CALLED SOMETHING THAT THEY HAVENT DECLARed
            /// MYTODO: Maybe this should throw an error
            return details::type_value<T>::convert(details::type_value<T>::default_value());
        }
        auto parse(int argc, char** argv) -> bool {            
            for (int i = 1; i < argc; ++i) { // First arg is the path of the program
                if ('-' == argv[i][0]) {
                    // The argument is an option or flag
                    const std::string_view sv_argv(argv[i]);                    

                    // Isolate the identifier from a potential value
                    const size_t equals_offset = sv_argv.find_first_of('=', 2);
                    const std::string_view identifier_name(sv_argv.begin(), std::string_view::npos == equals_offset ? sv_argv.end() : sv_argv.begin() + equals_offset);
                    option_entry* entry = get_option(identifier_name);

                    if (nullptr == entry) {
                        if ('-' != sv_argv[i] && sv_argv.size() > 2) { // Handle combined short flags                            
                            for (myl::usize s = 1; s != sv_argv.size(); ++s) {
                                // Isolate each short flag
                                entry = get_option(std::string("-") + sv_argv[s]);
                                if (nullptr == entry) { // Entry does not exist                                    
                                    failed_parse(std::string(std::string("-") + sv_argv[s]) + ": This option does not exist 2");
                                    return false;
                                }
                                else if (entry->seen) {                                    
                                    failed_parse(std::string(std::string("-") + sv_argv[s]) + ": This option has already been seen");
                                    return false;
                                }

                                entry->seen = true;
                                entry->data = "true"; // Flags can only be booleans
                            }

                            continue;
                        }

                        failed_parse(std::string(argv[i]) + ": This option does not exist");
                        return false;
                    }

                    // Handle flags and options

                    if (entry->seen) {
                        failed_parse(std::string(sv_argv) + ": This option has already been seen");
                        return false;
                    }

                    entry->seen = true;                    
                    if (0 == entry->arg_count) { // Handle flags                        
                        entry->data = "true"; // Flags can only be booleans
                    }
                    else { // Handle options
                        std::vector<std::string_view> values{};
                        values.reserve(entry->arg_count);

                        // Distinguish between the 2 supported formats for options with values; -a=1,2 vs -a 1 2                        
                        size_t offset = sv_argv.find_first_of('=', 2); /// use equals_offset
                        if (std::string_view::npos == offset) {
                            // Format: -a 1 2
                            ++i; // Skip over identifier (a)
                            while (i < argc) {
                                if ('-' == argv[i][0]) // Check if the new arg is an identifier
                                    break;
                            
                                values.push_back(argv[i]);
                                ++i;
                            }
                            --i; // Decrement, otherwise when the main loop (i) loops an arg will get skipped
                        }
                        else {
                            // Format: -a=1,2
                            while (offset < sv_argv.size()) {
                                ++offset; // Skip over delimiters '=' or ','
                                /// MYTODO: This will fail if ',' is in an input string or something like that
                                size_t delimiter = sv_argv.find_first_of(',', offset);
                                if (std::string_view::npos == delimiter)
                                    delimiter = sv_argv.size();

                                if (delimiter == offset) { // Empty value, syntax error
                                    failed_parse(std::string(sv_argv) + ": Incorrect list syntax");
                                    return false;
                                }

                                values.push_back(sv_argv.substr(offset, delimiter - offset));
                                offset += delimiter - offset;
                            }
                        }

                        if (values.size() != entry->arg_count) {
                            failed_parse(std::string(sv_argv) + ": Incorrect argument count provided");
                            return false;
                        }

                        std::string data{ "" };
                        for (auto& value : values) {
                            if (!data.empty())
                                data += ',';
                            data.append(value);
                        }

                        entry->data = data;
                    }

                }
                else {
                    /// MYTODO:
                    // The argument is either positional or an error
                }
            }

            return true;
        }

        auto help_message() const -> void {
            std::cout << m_program_name << std::endl;
            /// MYTODO: Maybe add a help message
            for (auto& entry : m_options) {
                std::string hint_message = entry.short_name;
                if (hint_message.empty())
                    hint_message = entry.long_name;
                else if (!entry.long_name.empty())
                    hint_message += ", " + entry.long_name;
                else // Both entry.short_name and entry.long_name are empty
                    ; /// MYTODO: THIS SHOULD NOT BE REACHABLE

                std::cout << hint_message << std::endl << '\t' << entry.help_message << std::endl;
            }
        }

        template<typename T>
        auto add_argument(const command_line_option& option) -> void {
            option_entry entry(option);
                        
            // Assign default value if user did not
            if (entry.default_value.empty())
                entry.default_value = details::type_value<T>::default_value();

            m_options.emplace_back(std::move(entry));
        }

    private:
        static auto default_error_callback(const std::string& message) -> void {
            std::cerr << message << std::endl;
        }

        auto failed_parse(const std::string& error_message) -> void {
            (*m_error_callback)(error_message);
            for (auto& entry : m_options)
                entry.seen = false; // Marked as not seen to effectively ignore any input being accessed
        }

        constexpr auto get_option(std::string_view option_name) -> option_entry* {
            for (auto& entry : m_options)
                if (entry.short_name == option_name || entry.long_name == option_name)
                    return &entry;
            return nullptr;
        }
    };
}
#else
#pragma once
#include <myl/definitions.hpp>

#include <format>
#include <iostream>
#include <string>
#include <string_view> /// MAYBE REMOVE
#include <utility>
#include <vector>

/// MYTODO: Tests to pass:
/// - -a : Short flags
/// - -a 1 : Short flags with a value
/// - -a (?) : Short flags with no value provided but has a default value
/// - -a 1,2 : Short flags with multiple values
/// - -a=1 : Short Flags with = value
/// - -a=1,2 : Shaft Flags with = with multiple values
/// - -abc : Short combined flags
/// - --aa : Long flags
/// - --aa 1 : Long flags with a value
/// - --aa (?) : Long flags with no value provided but has a default value
/// - --aa 1,2 : Long flags with multiple values
/// - --aa=1 : Long Flags with = value
/// - --aa=1,2 : Long Flags with = with multiple values
/// - a b c : Positional args
/// - 1 2 3 4 5 6 : Positional args with multiple values (Spaces)
/// - 1,2 3,4 5,6 : Positional args with multiple values (commas)
/// 
/// -a 1 2 3 ... : Short flags with an unknown amount of arguments. 
/// -a 1 2 3 ... -b : Short flags with an unknown amount of arguments followed by more options
/// --aa 1 2 3 ... : Long flags with an unknown amount of arguments. 
/// --aa 1 2 3 ... --bb : Long flags with an unknown amount of arguments followed by more options
/// 
/// Handle when dupelicate options are used
/// 
/// make it so it is possible that certain options will conflict or may also require another option to be set

/// Something here will probs break on --a

namespace myl {
    /// MYTODO: add this to string.hpp
    template<typename T>
    MYL_NO_DISCARD constexpr auto filter(std::basic_string_view<T> in, T character) -> std::basic_string<T> {
        std::basic_string<T> out;
        out.reserve(in.size());
        for (std::basic_string<T>::size_type i = 0; i != in.size(); ++i)
            if (in[i] != character)
                out += in[i];
        return out;
    }
    
    ///MYTODO: move to string
    template<const std::string_view&... Strings> /// MYTODO: Add something that allows any type of basic string view
    MYL_NO_DISCARD consteval auto concatenate() {
        constexpr std::string_view::size_type total_length = (Strings.size() + ...);
        std::array<std::string_view::value_type, total_length + 1> result;

        std::string_view::size_type offset = 0;
        auto append = [&](std::string_view sv) {
            std::copy(sv.begin(), sv.end(), result.begin() + offset);
            offset += sv.size();
            };
        (append(Strings), ...);

        result[total_length] = '\0';
        return result;
    }

    enum class command_line_argument_type { /// Maybe make internal to parse section
        unknown = -1,
        positonal,
        option,
        combined_flags,

        data = positonal
    };

    struct command_line_entry_data {
        const std::string name{ "" };
        const char short_name{ 0 };
        const std::string help_message{ "" };
        const myl::u16 arg_count{ 0 };
        const std::string default_value{ "" };
    };

    struct command_line_entry {  /// Maybe make internal to parser
        const command_line_entry_data data;
        command_line_argument_type type; /// IS THIS NEEDED in here?
        std::string value;
        bool seen;
    };

    class command_line_parser {
        std::string m_parser_name;
        std::vector<command_line_entry> m_entries;
        void (*m_error_callback)(std::string_view);        
    public:
        command_line_parser(const std::string name, void (*error_callback)(std::string_view) = nullptr)
            : m_parser_name{ name }
            , m_entries{}
            , m_error_callback{ error_callback == nullptr ? &command_line_parser::default_error_callback : error_callback } {}

        ///template<typename It1, typename It2>
        ///command_line_parser(const std::string name, It1 argument_begin, It1 argument_end, It2 option_begin, It2 option_end, void (*error_callback)(std::string_view) = nullptr)
        ///    : m_parser_name{ name }
        ///    , m_arguments(argument_begin, argument_end) /// MYTODO: Need to verify inputs
        ///    , m_options(option_begin, option_end) /// MYTODO: Need to verify inputs
        ///    , m_error_callback{ error_callback == nullptr ? &command_line_parser::default_error_callback : error_callback } {}

        ~command_line_parser() = default;

        auto help_message() const -> std::string { /// WIP
            std::string help_msg{ m_parser_name };

            /// MYTODO: Emit message format, build this from arguments and options

            for (const auto& entry : m_entries) {
                /// MYTODO: have an option that will hide the option from being printed in the help message
                /// same with showing the deafault value
                /// 
                /// also I wonder if all this construction is possible during compile time and can be stored as a var,
                /// however this is not important because this should not be a common function to call

                ///if (option.hide_from_help_message)
                ///    continue;

                if (!entry.data.name.empty() && entry.data.short_name != 0)
                    help_msg.append(std::format("\n--{}, -{}", entry.data.name, entry.data.short_name));
                else if (!entry.data.name.empty())
                    help_msg.append(std::format("\n--{}", entry.data.name));
                else if (entry.data.short_name != 0)
                    help_msg.append(std::format("\n-{}", entry.data.short_name));
                else {
                    /// std::unreachable(); need c++ 23
                    /// MYTODO: Mark as something that should be unreachable
                }

                if (entry.data.arg_count != 0)
                    help_msg.append(std::format("\n\tArgument count: {}", entry.data.arg_count));

                if (!entry.data.default_value.empty())
                    help_msg.append(std::format("\n\tDefault value: {}", entry.data.default_value));

                if (!entry.data.help_message.empty())
                    help_msg.append(std::format("\n\t{}", entry.data.help_message));
            }

            return help_msg;
        }

        /// MAKE ONCE FOR POSITIONAL VALUES, errors will be coming after an entry was submitted
        auto add_entry(const command_line_entry_data& data) -> void {
            MYL_ASSERT(data.name != "" || data.short_name != 0, "Missing entry name");
            MYL_ASSERT(!has_naming_conflict(data.name, data.short_name), "Naming conflict");
            
            m_entries.emplace_back(command_line_entry{
                .data  = data,
                .type  = command_line_argument_type::unknown, /// i think i shouold remove
                .value = "",
                .seen  = false
            });
        }

        auto parse(int arg_count, char** arg_values) -> bool {
            const std::vector<std::string> input_args(arg_values, arg_values + arg_count);

            // Set i to 1 to skip over the path
            for (std::vector<std::string>::size_type i = 1; i < input_args.size(); ++i) {
                switch (determine_command_line_argument_type(input_args[i])) {
                case command_line_argument_type::positonal: {
                    /// Verify its not data , the opsitional is suposed to be here
                    failed_parse("Not implemented");
                    return false;
                    break;
                }
                case command_line_argument_type::option: {
                    command_line_entry* entry = get_entry(input_args[i]);
                    if (entry == nullptr) {
                        failed_parse(error_invalid_key_argument(*this, input_args[i]));
                        return false;
                    }
                    else if (entry->seen) {
                        failed_parse(error_duplicate_key_argument(*this, input_args[i]));
                        return false;
                    }

                    if (entry->data.arg_count == 0) // Handle flags
                        entry->value = "1";
                    else { // Handle options
                        std::string value{ "" };
                        myl::u32 offset = i + 1;

                        while (offset != input_args.size()) {
                            if ('-' == input_args[offset][0]) { // Next identifier has been found
                                if (entry->data.default_value.empty()) { // Option has no data args following
                                    failed_parse(error_insufficent_arguments_provided(*this, input_args[i]));
                                    return false;
                                }
                                break; // Default value will be assigned
                            }

                            if (!value.empty())
                                value.append(",");
                            value.append(input_args[offset]);
                            ++offset;
                        }

                        --offset;
                        if (offset - i != 0 && offset - i != entry->data.arg_count) { // No idea but it works && Not enough arguments provided
                            failed_parse(error_insufficent_arguments_provided(*this, input_args[i]));
                            return false;
                        }

                        i = offset;
                        entry->value = value.empty() ? entry->data.default_value : value;
                    }

                    entry->seen = true;
                    break;
                }
                case command_line_argument_type::combined_flags: {
                    for (std::string::size_type j = 1; j != input_args[i].size(); ++j) { // Skip over the - in the first index
                        // Check if the flag is valid
                        command_line_entry* entry = get_entry(std::string_view(&input_args[i][j], 1));
                        if (entry == nullptr) {
                            failed_parse(error_invalid_key_argument(*this, input_args[i]));
                            return false;
                        }
                        else if (entry->seen) {
                            failed_parse(error_duplicate_key_argument(*this, std::string(&input_args[i][j], 1) + "' within '" + input_args[i]));
                            return false;
                        }

                        entry->value = "1";
                        entry->seen = true;
                    }
                    break;
                }
                case command_line_argument_type::unknown:
                    /// ERROR Should never happen
                    /// MYTODO: Fill out
                    failed_parse("Should not be possible");
                    return false;
                    break;
                default:
                    /// MYTODO: Mark as unreachable
                    failed_parse("Should not be possible");
                    return false;
                    break;
                }
            }

            return true;
        }
    private:
        inline static auto default_error_callback(std::string_view message) -> void {
            std::cerr << message;
        }

        MYL_NO_DISCARD inline static auto error_invalid_key_argument(const command_line_parser& parser, std::string_view key_name) -> std::string {
            return std::format("Parser '{}': Invalid key argument - Key '{}' is not valid.", parser.m_parser_name, key_name);
        }

        MYL_NO_DISCARD inline static auto error_duplicate_key_argument(const command_line_parser& parser, std::string_view key_name) -> std::string {
            return std::format("Parser '{}': Duplicate key - Duplicate keys ('{}') cannot be submitted.", parser.m_parser_name, key_name);
        }

        MYL_NO_DISCARD inline static auto error_insufficent_arguments_provided(const command_line_parser& parser, std::string_view key_name) -> std::string {
            return std::format("Parser '{}': Syntax error - Insufficent arguments following '{}'.", parser.m_parser_name, key_name);
        }

        auto failed_parse(const std::string& error_message) -> void {
            (*m_error_callback)(error_message);
            for (auto& entry : m_entries) {
                entry.value = entry.data.default_value;
                entry.seen = false;
            }
        }

        MYL_NO_DISCARD auto get_entry(std::string_view signature) -> command_line_entry* {
            const std::string pretty_signature{ filter(signature, '-') };
            for (auto& entry : m_entries)
                if (pretty_signature == entry.data.name || pretty_signature == std::string_view(&entry.data.short_name, 1))
                    return &entry;

            return nullptr;
        }

        MYL_NO_DISCARD constexpr auto determine_command_line_argument_type(std::string_view argument) const -> command_line_argument_type {
            if (argument[0] == '-') {
                if (argument[1] == '-' || (argument[1] != '-' && argument.size() == 2)) // Short and long named options
                    return command_line_argument_type::option;
                else if (argument[1] != '-' && argument.size() > 2)
                    return command_line_argument_type::combined_flags; /// maybe have this one first and check no =
                else /// This must be an error, or possibley a positional or input arg
                    return command_line_argument_type::unknown;
            }
            else /// THIS IS POSITIONAL OR DATA OR IF IT"S NOT it is an error
                return command_line_argument_type::positonal;
        }

#ifdef MYL_DEBUG
        MYL_NO_DISCARD auto has_naming_conflict(std::string_view name, const char short_name) const -> bool {
            for (const auto& entry : m_entries)
                if ((!entry.data.name.empty() && entry.data.name == name) || (entry.data.short_name != 0 && entry.data.short_name == short_name))
                    return true;
            return false;
        }
#endif
    };
}
#endif
