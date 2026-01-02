#pragma once
#include <myl/definitions.hpp>

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

/// Rewrite entire thing for final class

/// MYTODO: fix the types choosen

/// Inputs wanted
// Long flag, --help
// short flag, -h
/// long option, --output file.txt
/// long option equals, --output=file.txt
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

        auto parse(int argc, char** argv) -> bool { /// CHANGED != to < veryify that works
            for (int i = 1; i < argc; ++i) { // First arg is the path of the program
                if ('-' == argv[i][0]) { // Handle flags, options
                    const std::string_view svargv(argv[i]);

                    const size_t equals_offset = svargv.find_first_of('=', 2);
                    const std::string_view identifier_name(svargv.begin(), std::string_view::npos == equals_offset ? svargv.end() : svargv.begin() + equals_offset);
                    option_entry* option = get_option(identifier_name);

                    if (nullptr == option) {                        
                        if ('-' != svargv[1] && svargv.size() > 2) {
                            // Handle combined short flags

                            for (int j = 1; j != svargv.size(); ++j) {
                                option = get_option(std::string("-") + svargv[j]);
                                if (nullptr == option) { /// Improve short flag error
                                    failed_parse(std::string(std::string("-") + svargv[j]) + ": This option does not exist");
                                    return false;
                                }

                                option->seen = true;
                                option->data = "true"; // Flags can only be bools
                            }

                            continue;
                        }

                        failed_parse(std::string(argv[i]) + ": This option does not exist");
                        return false;
                    }

                    option->seen = true;
                    
                    if (0 == option->arg_count) {
                        // Handle short and long flags
                        option->data = "true";
                    }
                    else {                        
                        // Handle options with values
                        std::string list{ "" };
                        
                        // Check for args being defined with an '='
                        const size_t param_offset = svargv.find_first_of('=', 2);
                        if (std::string_view::npos == param_offset) {
                            /// MYTODO: This could probs be improved
                            // This section handles arguments when they're in the next argv(s)
                            for (int expected_arg_count = option->arg_count; expected_arg_count != 0; --expected_arg_count) {
                                ++i; // Skip the identifier
                                if ('-' == argv[i][0]) { // Check that the new arg is a parameter
                                    failed_parse(std::string(svargv) + ": is not followed by the expected amount of arguments (enter num)");
                                    return false;
                                }

                                if (!list.empty())
                                    list += ",";
                                list.append(argv[i]);
                            }
                        }
                        else {
                            // This section handles arguments when they're in the same argv
                            /// MYTODO: These should be verified to prevent security risks
                            /// eg like arg count and syntax
                            list.append(svargv.begin() + param_offset + 1, svargv.end());
                            
                            ///size_t offset = svargv.find_first_of('=', 2);
                            ///while (std::string_view::npos != offset) {
                            ///    ++offset;
                            ///    const size_t next_offset = svargv.find_first_of(',', offset);
                            ///    if (std::string_view::npos == next_offset) {
                            ///        if (!list.empty())
                            ///            list += ",";
                            ///        list.append(svargv.begin() + offset, svargv.end());
                            ///        break;
                            ///    }
                            ///
                            ///    std::string_view arg(svargv.begin() + offset, svargv.begin() + next_offset);
                            ///    std::cout << arg << std::endl;
                            ///
                            ///    offset = next_offset;
                            ///}
                        }
                            
                        /// Handle
                        /// -h=1
                        /// -h 1                        
                        /// --help=1
                        /// --help 1
                    
                        option->data = list;
                    }
                }
                else {
                    /// It's a positional arg or
                    /// a value to a key, which should have be handled above
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
            std::cout << message << std::endl;
        }

        auto failed_parse(const std::string& error_message) -> void {
            (*m_error_callback)(error_message);
            for (auto& entry : m_options)
                entry.seen = false;
        }

        constexpr auto get_option(std::string_view option_name) -> option_entry* {
            for (auto& entry : m_options)
                if (entry.short_name == option_name || entry.long_name == option_name)
                    return &entry;
            return nullptr;
        }
    };
}
