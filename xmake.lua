
add_rules("mode.debug", "mode.release")

set_languages("cxx17")

target("d3d11")
    set_kind("shared")

    add_files("src/main.cpp")
    add_files("src/console.cpp")

    set_targetdir("build")

