#pragma once

// [Python/C API] Debug 빌드 시, "Python27_d.lib" 에러
// https://kiya.tistory.com/2
// (pyconfig.h, object.h 수정 필요)

// https://stackoverflow.com/questions/23068700/embedding-python3-in-qt-5
#   pragma push_macro("slots")
#   undef slots

#       define PY_SSIZE_T_CLEAN
#       include <Python.h>

#   pragma pop_macro("slots")
