set(PACKAGE_NAME "ncPhysic")
set(PACKAGE_EXE_NAME "ncphysic")
set(PACKAGE_VENDOR "Tonaion")
set(PACKAGE_COPYRIGHT "Copyright ©2019-2021 ${PACKAGE_VENDOR}")
set(PACKAGE_DESCRIPTION "ncPhysic")
set(PACKAGE_HOMEPAGE "https://ncine.github.io")
set(PACKAGE_REVERSE_DNS "io.github.ncine.nctemplate")

set(PACKAGE_INCLUDE_DIRS src)

file(GLOB ANIMATION_FILES "src/Animation/*.h" "src/Animation/*.cpp")
file(GLOB INPUT_FILES "src/Input/*.h" "src/Input/*.cpp")
file(GLOB ITEM_FILES "src/item/*.h" "src/item/*.cpp")
file(GLOB MENU_FILES "src/Menu/*.h" "src/Menu/*.cpp")
file(GLOB RENDERER_FILES "src/Renderer/*.h" "src/Renderer/*.cpp")
file(GLOB VFX_FILES "src/vfx/*.h" "src/vfx/*.cpp")
file(GLOB WORLD_FILES "src/world/*.h" "src/world/*.cpp")
file(GLOB PHYSIC_FILES "src/Physic/*.h" "src/Physic/*.cpp")
file(GLOB GAMEOBJECT_FILES "src/GameObject/*.h" "src/GameObject/*.cpp")
	
set(PACKAGE_SOURCES
	src/main.h
	src/main.cpp
	
	src/Player.cpp
	src/Player.h
	
	src/PrecompiledHeaders.h	
	src/PrecompiledHeaders.cpp	
	src/AddonsString.h
	src/AddonsString.cpp
	src/Image.cpp
	src/Image.h
	src/StaticImage.h
	src/StaticImage.cpp
	
	src/vendor/stdbimage.cpp
	
	${ANIMATION_FILES}
	${INPUT_FILES}
	${ITEM_FILES}
	${MENU_FILES}
	${RENDERER_FILES}
	${VFX_FILES}
	${WORLD_FILES}
	${PHYSIC_FILES}
	${GAMEOBJECT_FILES}
)

function(callback_end)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	source_group("Animation" FILES ${ANIMATION_FILES})

	source_group("Input" FILES ${INPUT_FILES})

	source_group("item" FILES ${ITEM_FILES})

	source_group("Menu" FILES ${MENU_FILES})

	source_group("Renderer" FILES ${RENDERER_FILES})

	source_group("vfx" FILES ${VFX_FILES})

	source_group("world" FILES ${WORLD_FILES})
	
	source_group("Physic" FILES ${PHYSIC_FILES})
	
	source_group("GameObject" FILES ${GAMEOBJECT_FILES})
endfunction()