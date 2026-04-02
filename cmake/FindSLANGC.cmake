find_program(SLANGC_EXECUTABLE slangc
  HINTS ENV SLANG_HOME
  HINTS ENV PATH
)

if(NOT SLANGC_EXECUTABLE)
  message(FATAL_ERROR "Could not find slangc. Please install shader-slang or set SLANG_HOME or PATH.")
endif()


set(SLANGC_FOUND TRUE)

message(STATUS "Found slangc at: ${SLANGC_EXECUTABLE}")

function(embed_slang_shader TARGET_NAME INTERFACE SHADER_PATH)
  if (NOT Python_EXECUTABLE)
    message(FATAL_ERROR "Please find Python!")
  endif()
  
  get_filename_component(SHADER_ABS ${SHADER_PATH} ABSOLUTE)
  
  get_filename_component(SHADER_NAME ${SHADER_PATH} NAME_WE)
  get_filename_component(SHADER_EXT ${SHADER_PATH} EXT)

  string(TOUPPER "${SHADER_NAME}" SHADER_NAME_CAP)

  set(HEADER_VERT_PATH "${CMAKE_BINARY_DIR}/${SHADER_NAME}_vert.h")
  set(HEADER_FRAG_PATH "${CMAKE_BINARY_DIR}/${SHADER_NAME}_frag.h")

  add_custom_command(
    OUTPUT ${HEADER_VERT_PATH} ${HEADER_FRAG_PATH}
    COMMAND ${Python_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/gen_slang_shader.py ${SLANGC_EXECUTABLE} ${SHADER_ABS} ${CMAKE_BINARY_DIR}
    DEPENDS ${SHADER_ABS} ${CMAKE_SOURCE_DIR}/scripts/gen_slang_shader.py
    COMMENT "Compiling shader ${SHADER_NAME}..."
  )

  add_custom_target(
    CompileShader${SHADER_NAME} ALL
    DEPENDS ${HEADER_VERT_PATH} ${HEADER_FRAG_PATH}
  )

  add_dependencies(${TARGET_NAME} CompileShader${SHADER_NAME})

  target_compile_definitions(${TARGET_NAME} ${INTERFACE} ${SHADER_NAME_CAP}_VERT=\"${HEADER_VERT_PATH}\")
  target_compile_definitions(${TARGET_NAME} ${INTERFACE} ${SHADER_NAME_CAP}_FRAG=\"${HEADER_FRAG_PATH}\")
endfunction()
