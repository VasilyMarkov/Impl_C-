set(OPTIONS -fno-elide-constructors) #RVO disable
add_executable(smart smart_pointers.cpp)
add_executable(rvo_ref rvo_ref.cpp)
# target_compile_options(rvo_ref PUBLIC "${OPTIONS}")