/* date = July 5th 2023 8:31 am */

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <stdint.h>
#include <stdbool.h>

// Costum implementation of std::pair<typename, typename>
#define PAIR(ta, tb)     struct { ta a; tb b; }

typedef int8_t         i8;
typedef int16_t        i16;
typedef int32_t        i32;
typedef int64_t        i64;

typedef uint8_t        u8;
typedef uint16_t       u16;
typedef uint32_t       u32;
typedef uint64_t       u64;

typedef float          f32;
typedef double         f64;

#undef  enum
#define enum(name)       typedef enum name name; enum name
#define class(name)      typedef struct name name; struct name
#define internal         static
#define local_persist    static
#define global           static

#endif //TYPEDEF_H