#ifndef __generator_h__
#define __generator_h__

// generator/continuation for C++
// author: Andrew Fedoniouk @ terrainformatica.com
// idea borrowed from: "coroutines in C" Simon Tatham,
//   http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html

class _generator
{
protected:
	int _line;
public:
	_generator() :_line(0) {}
};

#define $generator(NAME) struct NAME : public _generator

#define $emit(T) bool operator()(T& _rv) { \
                    switch(_line) { case 0:;

#define $stop  } _line = 0; return false; }

#define $yield(V)     \
        do {\
            _line=__LINE__;\
            _rv = (V); return true; case __LINE__:;\
        } while (0)
#endif