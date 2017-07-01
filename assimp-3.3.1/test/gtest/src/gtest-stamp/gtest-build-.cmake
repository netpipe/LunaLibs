

set(command "${make}")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/media/clay/0ca40d09-7d15-49f2-8630-1f2258a0a8c8/tecan/games/Luna/LunaLibs/assimp-3.3.1/test/gtest/src/gtest-stamp/gtest-build-out.log"
  ERROR_FILE "/media/clay/0ca40d09-7d15-49f2-8630-1f2258a0a8c8/tecan/games/Luna/LunaLibs/assimp-3.3.1/test/gtest/src/gtest-stamp/gtest-build-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /media/clay/0ca40d09-7d15-49f2-8630-1f2258a0a8c8/tecan/games/Luna/LunaLibs/assimp-3.3.1/test/gtest/src/gtest-stamp/gtest-build-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest build command succeeded.  See also /media/clay/0ca40d09-7d15-49f2-8630-1f2258a0a8c8/tecan/games/Luna/LunaLibs/assimp-3.3.1/test/gtest/src/gtest-stamp/gtest-build-*.log")
  message(STATUS "${msg}")
endif()
