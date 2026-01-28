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
        MYL_NO_DISCARD constexpr command_line_parser(const std::string& program_name, void (*error_callback)(const std::string&) = nullptr)
            : m_program_name{ program_name }
            , m_error_callback{ error_callback == nullptr ? &command_line_parser::default_error_callback : error_callback } {}

        constexpr ~command_line_parser() = default;

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
