    if (NOT DEFINED EXE_PATH)
      message(FATAL_ERROR "EXE_PATH no recibido")
    endif()
    if (NOT DEFINED DEST_DIR)
      message(FATAL_ERROR "DEST_DIR no recibido")
    endif()

    set(RUNTIME_DIRS C:/msys64/ucrt64/bin;C:/msys64/mingw64/bin;C:/msys64/clang64/bin)

    file(GET_RUNTIME_DEPENDENCIES
      RESOLVED_DEPENDENCIES_VAR DEPS
      UNRESOLVED_DEPENDENCIES_VAR UNRES
      EXECUTABLES "${EXE_PATH}"
      DIRECTORIES ${RUNTIME_DIRS}
      # ¡Claves!: excluir API sets *antes* de resolver y no copiar DLLs del propio Windows
      PRE_EXCLUDE_REGEXES  "api-ms-.*" "ext-ms-.*"
      POST_EXCLUDE_REGEXES "Windows\\\\SYSTEM32.*" "Windows\\\\SysWOW64.*"
    )

    foreach(f ${DEPS})
      file(COPY "${f}" DESTINATION "${DEST_DIR}")
    endforeach()

    if (UNRES)
      message(STATUS "[CMake] Dependencias no resueltas (ignoradas):")
      foreach(u ${UNRES})
        message(STATUS "  - ${u}")
      endforeach()
    endif()

    message(STATUS "[CMake] DLLs copiadas a: ${DEST_DIR}")
  
