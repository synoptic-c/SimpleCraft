cmake_minimum_required(VERSION 3.12)
project(SimpleCraft)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(/wd26819)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(External/GLFW)
set(EXTERNAL
	External/glad/glad.c
	External/stb/stb_image.cpp
	External/stb/stb_truetype.cpp
)
set(UTIL
	Source/Util/Log.hpp
	Source/Util/Log.cpp
	Source/Util/Timer.hpp
	Source/Util/Timer.cpp
	Source/Util/Trigger.hpp
	Source/Util/Trigger.cpp
	Source/Util/Input.hpp
	Source/Util/Input.cpp
)
set(GRAPHICS
	Source/Graphics/ContextGL.hpp
	Source/Graphics/ContextGL.cpp
	Source/Graphics/GraphicsSettings.hpp
	Source/Graphics/GraphicsSettings.cpp
	Source/Graphics/Window.hpp
	Source/Graphics/Window.cpp
	Source/Graphics/VertexArray.hpp
	Source/Graphics/VertexArray.cpp
	Source/Graphics/VertexBuffer.hpp
	Source/Graphics/VertexBuffer.cpp
	Source/Graphics/IndexBuffer.hpp
	Source/Graphics/IndexBuffer.cpp
	Source/Graphics/Mesh.hpp
	Source/Graphics/Mesh.cpp
	Source/Graphics/Shader.hpp
	Source/Graphics/Shader.cpp
	Source/Graphics/Texture.hpp
	Source/Graphics/Texture.cpp
	Source/Graphics/Font.hpp
	Source/Graphics/Font.cpp
	Source/Graphics/MeshManager.hpp
	Source/Graphics/MeshManager.cpp
	Source/Graphics/ShaderManager.hpp
	Source/Graphics/ShaderManager.cpp
	Source/Graphics/FontManager.hpp
	Source/Graphics/FontManager.cpp
	Source/Graphics/FontRender.hpp
	Source/Graphics/FontRender.cpp
	Source/Graphics/Camera.hpp
	Source/Graphics/Camera.cpp
	Source/Graphics/Atlas.hpp
	Source/Graphics/Atlas.cpp
	Source/Graphics/Animation.hpp
	Source/Graphics/Animation.cpp
)
set(ENTITY
	Source/Entity/Player.hpp
	Source/Entity/Player.cpp
	Source/Entity/Drop.hpp
	Source/Entity/Drop.cpp
)
set(WORLD
	Source/World/Structure.hpp
	Source/World/Structure.cpp
	Source/World/Tile.hpp
	Source/World/Tile.cpp
	Source/World/Ore.hpp
	Source/World/Ore.cpp
	Source/World/Chunk.hpp
	Source/World/Chunk.cpp
	Source/World/World.hpp
	Source/World/World.cpp
)
set(PHYSICS
	Source/Physics/Bound.hpp
	Source/Physics/Bound.cpp
	Source/Physics/BoundManager.hpp
	Source/Physics/BoundManager.cpp
	Source/Physics/Collision.hpp
	Source/Physics/Collision.cpp
	Source/Physics/Overlap.hpp
	Source/Physics/Overlap.cpp
)
set(CONTAINER
	Source/Container/Inventory.hpp
	Source/Container/Inventory.cpp
	Source/Container/Item.hpp
	Source/Container/Item.cpp
)
set(EDIT
	Source/Edit/Cursor.hpp
	Source/Edit/Cursor.cpp
)
set(CORE
	Source/Core/Main.cpp
)
add_executable(SimpleCraft #WIN32
	${EXTERNAL}
	${UTIL}
	${GRAPHICS}
	${ENTITY}
	${WORLD}
	${PHYSICS}
	${CONTAINER}
	${EDIT}
	${CORE}
)
target_include_directories(${PROJECT_NAME} PRIVATE
	External/GLFW/include
	External/stb
	External
	Source
)
#set_target_properties(SimpleCraft PROPERTIES
#    LINK_FLAGS "/ENTRY:mainCRTStartup"
#)
target_link_libraries(${PROJECT_NAME} PRIVATE
	glfw
	opengl32
)
add_custom_command(TARGET SimpleCraft POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:SimpleCraft>/Assets
)