add_executable(glTests
    main.cpp
)

create_target_directory_groups(glTests)

target_link_libraries(glTests PRIVATE common)
target_link_libraries(glTests PRIVATE glad glfw)
