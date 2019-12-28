find_program(CLANG_TIDY NAMES clang-tidy)

file(GLOB_RECURSE CLANG_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

if(CLANG_TIDY)
    add_custom_target(
        clang-tidy
        ${CLANG_TIDY}
        # Suppress messages
        #-quiet #TODO temp disable
        # Path to compilation data base.
        -p=${CMAKE_BINARY_DIR}
        # Only produce errors for headers in repo
        -header-filter=.*
        # Enable all checks and then disable some
        -checks=*,\\
        # Treat all warnings as errors.
        -warnings-as-errors=*,\\
        # TODO temporariraly disable to reduce errors
        -hicpp-braces-around-statements,\\
        -modernize-use-using,\\
        -modernize-use-override,\\
        # Disable the following checkers because they're not useful / not needed / produced a lot of false positives.
        -cppcoreguidelines-pro-bounds-array-to-pointer-decay,\\ # This generates a lot of false positives.
        -hicpp-no-array-decay,\\ # This generates a lot of false positives.
        -fuchsia-default-arguments,\\ # We allow default arguments.
        -llvm-include-order,\\ # Too stylistic.
        -google-readability-todo,\\ # missing username/bug in TODOs
        -cppcoreguidelines-pro-type-union-access,\\ # suggests boost
        -fuchsia-overloaded-operator,\\ # cannot overload operator++
        -clang-diagnostic-error,\\ # About clang not finding headers.
        -misc-unused-alias-decls,\\ # False positives.
        -llvm-header-guard,\\ # Style - llvm header guard style
        -modernize-pass-by-value,\\ # Only for proper sinks, don't want to deal with these errors.
        -readability-avoid-const-params-in-decls,\\ # Doesn't disturbe
        -llvm-namespace-comment,\\ # Stylistic - useless for short namespaces.
        -performance-unnecessary-value-param,\\ # Generates noise for shared_pt, asks pass argument as const ref.
        # Disable these checkers because they're duplicates of other checkers.
        -hicpp-use-override,\\ # modernize-use-override
        -hicpp-use-equals-delete,\\ # modernize-use-equals-delete
        -hicpp-special-member-functions,\\ # cppcoreguidelines-special-member-functions
        -cert-err60-cpp,\\ # Similar to hicpp-exception-baseclass. Creates duplicate errors.
        -readability-braces-around-statements,\\ # hicpp-braces-around-statements
        -google-readability-braces-around-statements,\\ # hicpp-braces-around-statements
        -google-explicit-constructor,\\ # hicpp-explicit-conversions
        -google-readability-casting,\\ # cppcoreguidelines-pro-type-cstyle-cast
        -performance-noexcept-move-constructor # hicpp-noexcept-move
        ${CLANG_SOURCES}
        > ${CMAKE_BINARY_DIR}/clang-tidy-results.log || (exit 0)
    )
else(CLANG_TIDY)
    message(STATUS "clang-tidy SCA tool not found. apt-get install clang-tidy if you wish to run SCA.")
endif(CLANG_TIDY)

# Option to use tool to transform from clang-tidy results to JUnit format (Good for Jenkins).
find_program(CLANG_TIDY_TO_JUNIT NAMES clang-tidy-to-junit.py PATHS ${CMAKE_SOURCE_DIR}/scripts/clang-tidy-to-junit)
# Convert Junit xml file to html
find_program(JUNIT2HTML NAMES junit2html)

if(CLANG_TIDY_TO_JUNIT AND JUNIT2HTML)
    add_custom_target(
        junit
        COMMAND ${CLANG_TIDY_TO_JUNIT} ${CMAKE_SOURCE_DIR}/ < ${CMAKE_BINARY_DIR}/clang-tidy-results.log
        # Check if clang-tidy-junit.xml has any error
        | tee ${CMAKE_BINARY_DIR}/clang-tidy-junit.xml | grep 'errors="0"' || (exit 0)
        COMMAND ${JUNIT2HTML} ${CMAKE_BINARY_DIR}/clang-tidy-junit.xml ${CMAKE_BINARY_DIR}/clang-tidy-junit.html || (exit 0)
    )
else()
    message(STATUS "Can't transform clang-tidy results to junit. Missing clang-tidy-to-junit and junit2html.")
endif(CLANG_TIDY_TO_JUNIT AND JUNIT2HTML)
