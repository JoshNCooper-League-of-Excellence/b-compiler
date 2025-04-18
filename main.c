#define USE_STD_LIB 1

  typedef unsigned long long int u64;
  typedef signed long long int s64;

  typedef signed int s32;
  typedef unsigned int u32;

  typedef double f64;
  typedef float f32;

  typedef short int s16;
  typedef unsigned short int u16;

  typedef signed char s8;
  typedef unsigned char u8;
  #include <stddef.h>

  // I don't think we need any of these includes anymore.
  #if USE_STD_LIB
    #include <stdint.h>
    #include <errno.h>
    #undef RAND_MAX
  #endif

  #ifdef TESTING
    #if TEST_VERBOSE
      int printf(u8 *, ...);
    #endif

    typedef struct {
      const char *name;
      void (*function)();
    } $ela_test;

    static void $ela_test_run($ela_test *test) {
      #if TEST_VERBOSE
        printf("running %s\n", test->name);
      #endif
      test->function();
    }

  #endif
  
typedef struct Type Type;
typedef struct Dyn_Allocator Dyn_Allocator;
typedef struct List$146 {
  Type** data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$146;
typedef struct Type Type;
extern List$146 _type_info;
typedef struct str {
  u8* data;
  u64 length;
} str;
typedef struct $tuple18$213 {
  str $0;
  void* $1;
} $tuple18$213;
typedef struct Env Env;
typedef struct str str;
typedef struct Slice$18 {
  str* data;
  u64 length;
} Slice$18;
typedef struct Env {
  Slice$18 args_slice;
} Env;
Env* Env$current() {
  static Env self = {};
  return (&self);
}
extern void*  malloc(u64);
typedef struct RangeIter$1 {
  s32 begin;
  s32 end;
  s32 idx;
} RangeIter$1;
typedef struct RangeBase$1 {
  s32 begin;
  s32 end;
} RangeBase$1;
typedef struct RangeBase$1 RangeBase$1;
RangeIter$1 RangeBase$1$iter(RangeBase$1* self) {
  return (RangeIter$1){
    .begin = (s32)self->begin,
    .idx = (s32)self->begin,
    .end = (s32)self->end};
}
typedef struct $tuple1 {
  s32 $0;
} $tuple1;
typedef struct Option$1 Option$1;
typedef $tuple1 Option$1$Some;
typedef struct Option$1 {
  int index;
  union {
    Option$1$Some Some;
  };
} Option$1;
typedef struct RangeIter$1 RangeIter$1;
Option$1 Some$1(s32 t) {
  return (Option$1) {
.index = 0,
.Some = ($tuple1) {.$0 = t}};
}
Option$1 RangeIter$1$next(RangeIter$1* self) {
  if ((self->idx == self->end)) {
    return  (Option$1) { .index = 1};
  }
  Option$1 value  = Some$1(self->idx);
  if ((self->begin > self->end)) {
    self->idx--;
  }
  else{
    self->idx++;
  }
  return value;
}
extern u32  strlen(u8*);
void Env$initialize(s32 argc, u8** argv) {
  Env* self  = Env$current();
  str* data  = malloc((argc * sizeof(str)));
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = argc};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 i = $next.Some.$0;
      {
        (data[i] = (str){
          .data = (u8*)argv[i],
          .length = (u64)strlen(argv[i])});
      }
    }
  }
  (self->args_slice = (Slice$18){
    .data = (str*)data,
    .length = (u64)argc});
}
typedef struct List$1482 List$1482;
typedef struct List$1483 {
  List$1482* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$1483;
typedef struct map$Map$18_5 {
  List$1483 buckets;
  u64 length;
} map$Map$18_5;
typedef struct List$18 {
  str* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$18;
typedef struct elexify$State elexify$State;
typedef struct List$59 {
  elexify$State* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$59;
typedef struct elexify$Token elexify$Token;
typedef struct List$58 {
  elexify$Token* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$58;
typedef struct String {
  u8* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} String;
typedef struct elexify$Lexer {
  map$Map$18_5 operators;
  map$Map$18_5 keywords;
  List$18 reserved;
  List$59 states;
  List$58 lookahead_buffer;
  String reserved_placeholder;
} elexify$Lexer;
static constexpr u32 elexify$TOKEN_EOF  = (u32)(-1);
static constexpr u32 elexify$TOKEN_IDENTIFIER  = (u32)(-2);
static constexpr u32 elexify$TOKEN_INTEGER  = (u32)(-3);
static constexpr u32 elexify$TOKEN_FLOAT  = (u32)(-4);
static constexpr u32 elexify$TOKEN_STRING  = (u32)(-5);
static constexpr u32 elexify$TOKEN_CHAR  = (u32)(-6);
typedef enum {
  lexer$TType$Comma = 0,
  lexer$TType$Semicolon = 1,
  lexer$TType$Add = 2,
  lexer$TType$Sub = 3,
  lexer$TType$Div = 4,
  lexer$TType$Mul = 5,
  lexer$TType$Modulo = 6,
  lexer$TType$Assign = 7,
  lexer$TType$OpenParen = 8,
  lexer$TType$CloseParen = 9,
  lexer$TType$OpenCurly = 10,
  lexer$TType$CloseCurly = 11,
  lexer$TType$Extrn = 12,
  lexer$TType$Auto = 13,
  lexer$TType$If = 14,
  lexer$TType$Eof = elexify$TOKEN_EOF,
  lexer$TType$Identifier = elexify$TOKEN_IDENTIFIER,
  lexer$TType$Integer = elexify$TOKEN_INTEGER,
  lexer$TType$Float = elexify$TOKEN_FLOAT,
  lexer$TType$String = elexify$TOKEN_STRING,
  lexer$TType$Char = elexify$TOKEN_CHAR
} lexer$TType;
typedef struct $tuple18$5 $tuple18$5;
typedef struct InitList$1482 {
  $tuple18$5* data;
  u64 length;
} InitList$1482;
typedef struct Iter$1482 {
  $tuple18$5* ptr;
  $tuple18$5* end;
} Iter$1482;
typedef struct $tuple18$5 {
  str $0;
  u32 $1;
} $tuple18$5;
typedef struct InitList$1482 InitList$1482;
Iter$1482 InitList$1482$iter(InitList$1482* self) {
  return (Iter$1482){
    .ptr = ($tuple18$5*)($tuple18$5*)self->data,
    .end = ($tuple18$5*)(self->data + self->length)};
}
typedef struct $tuple1482 {
  $tuple18$5 $0;
} $tuple1482;
typedef struct Option$1482 Option$1482;
typedef $tuple1482 Option$1482$Some;
typedef struct Option$1482 {
  int index;
  union {
    Option$1482$Some Some;
  };
} Option$1482;
typedef struct Iter$1482 Iter$1482;
Option$1482 Iter$1482$next(Iter$1482* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$1482) { .index = 1};
  }
  Option$1482 value  = (Option$1482) {
.index = 0,
.Some = ($tuple1482) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
typedef struct map$Map$18_5 map$Map$18_5;
typedef struct List$1483 List$1483;
typedef struct Libc_Allocator {
} Libc_Allocator;
typedef struct Dyn_Allocator {
  void* instance;
  void*(*p_allocate)(void*, u64);
  void(*p_free)(void*, void*);
  void*(*p_allocate_array)(void*, u64, u64);
  void*(*p_resize)(void*, void*, u64, u64);
  void*(*p_copy)(void*, void*, u64, u64);
  void(*p_deinit)(void*);
} Dyn_Allocator;
typedef struct Libc_Allocator Libc_Allocator;
void* Libc_Allocator$allocate(Libc_Allocator* self, u64 size) {
  return malloc(size);
}
extern void  free(void*);
void Libc_Allocator$free(Libc_Allocator* self, void* ptr) {
  free(ptr);
}
extern void*  calloc(u64, u64);
void* Libc_Allocator$allocate_array(Libc_Allocator* self, u64 size, u64 n) {
  return calloc(size, n);
}
extern void*  realloc(void*, u64);
void* Libc_Allocator$resize(Libc_Allocator* self, void* ptr, u64 element_size, u64 new_size) {
  return realloc(ptr, (element_size * new_size));
}
extern void*  memcpy(void*, void*, u64);
void* Libc_Allocator$copy(Libc_Allocator* self, void* ptr, u64 element_size, u64 n) {
  void* newptr  = Libc_Allocator$allocate_array(self, element_size, n);
  memcpy(newptr, ptr, (n * element_size));
  return newptr;
}
void Libc_Allocator$deinit(Libc_Allocator* self) {
}
Dyn_Allocator Dyn_Allocator$new$35(Libc_Allocator* t) {
  return (Dyn_Allocator){
    .instance = (void*)t,
    .p_allocate = (void*(*)(void*, u64))(&Libc_Allocator$allocate),
    .p_free = (void(*)(void*, void*))(&Libc_Allocator$free),
    .p_allocate_array = (void*(*)(void*, u64, u64))(&Libc_Allocator$allocate_array),
    .p_resize = (void*(*)(void*, void*, u64, u64))(&Libc_Allocator$resize),
    .p_copy = (void*(*)(void*, void*, u64, u64))(&Libc_Allocator$copy),
    .p_deinit = (void(*)(void*))(&Libc_Allocator$deinit)};
}
Dyn_Allocator* new$34(Dyn_Allocator initial_value) {
  Dyn_Allocator* ptr  = malloc(sizeof(Dyn_Allocator));
  ((*ptr) = initial_value);
  return ptr;
}
Dyn_Allocator* get_default_allocator() {
  static Libc_Allocator allocator = {};
  static Dyn_Allocator* dynamic  = NULL;
  if ((dynamic == NULL)) {
    (dynamic = new$34(Dyn_Allocator$new$35((&allocator))));
  }
  return dynamic;
}
typedef struct List$1482 {
  $tuple18$5* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$1482;
void* Dyn_Allocator$resize(Dyn_Allocator* self, void* ptr, u64 element_size, u64 new_size) {
  void*(*p_resize)(void*, void*, u64, u64) = self->p_resize;
  return p_resize(self->instance, ptr, element_size, new_size);
}
void List$1483$resize(List$1483* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(List$1482), self->capacity));
}
extern void*  memset(void*, s32, u64);
void List$1483$initialize(List$1483* self, u64 num_to_fill) {
  List$1483$resize(self, num_to_fill);
  memset(self->data, 0, (sizeof(List$1482) * self->capacity));
  (self->length = num_to_fill);
}
typedef struct Iter$7 {
  u8* ptr;
  u8* end;
} Iter$7;
Iter$7 str$iter(str* self) {
  return (Iter$7){
    .ptr = (u8*)(u8*)self->data,
    .end = (u8*)(self->data + self->length)};
}
typedef struct $tuple7 {
  u8 $0;
} $tuple7;
typedef struct Option$7 Option$7;
typedef $tuple7 Option$7$Some;
typedef struct Option$7 {
  int index;
  union {
    Option$7$Some Some;
  };
} Option$7;
typedef struct Iter$7 Iter$7;
Option$7 Iter$7$next(Iter$7* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$7) { .index = 1};
  }
  Option$7 value  = (Option$7) {
.index = 0,
.Some = ($tuple7) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
u64 str$hash(str self) {
  u64 hash  = 0xCBF29CE484222325;
  {
    str $iterable = self;
    Iter$7 $iterator = str$iter(&$iterable);
    while (1) {
      auto $next = Iter$7$next(&$iterator);
      if (!$next.index != 1) break;
      u8 byte = $next.Some.$0;
      {
        (hash ^= byte);
        (hash *= 0x100000001B3);
      }
    }
  }
  return hash;
}
typedef struct IterMut$1482 {
  $tuple18$5* ptr;
  $tuple18$5* end;
} IterMut$1482;
List$1482* List$1483$subscript(List$1483* self, u64 idx) {
  return (&self->data[idx]);
}
IterMut$1482 List$1482$iter_mut(List$1482* self) {
  return (IterMut$1482){
    .ptr = ($tuple18$5*)self->data,
    .end = ($tuple18$5*)(self->data + self->length)};
}
typedef struct $tuple1484 {
  $tuple18$5* $0;
} $tuple1484;
typedef struct Option$1484 Option$1484;
typedef $tuple1484 Option$1484$Some;
typedef struct Option$1484 {
  int index;
  union {
    Option$1484$Some Some;
  };
} Option$1484;
typedef struct IterMut$1482 IterMut$1482;
Option$1484 IterMut$1482$next(IterMut$1482* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$1484) { .index = 1};
  }
  Option$1484 value  = (Option$1484) {
.index = 0,
.Some = ($tuple1484) {.$0 = self->ptr}};
  self->ptr++;
  return value;
}
u8* str$subscript(str* self, u64 idx) {
  return (&self->data[idx]);
}
bool str$eq(str self, str other) {
  if ((self.length != other.length)) {
    return false;
  }
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = self.length};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 idx = $next.Some.$0;
      {
        if (((*(str$subscript(&self, idx))) != (*(str$subscript(&other, idx))))) {
          return false;
        }
      }
    }
  }
  return true;
}
void List$1482$resize(List$1482* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof($tuple18$5), self->capacity));
}
void List$1482$push(List$1482* self, $tuple18$5 v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$1482$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
void map$Map$18_5$insert(map$Map$18_5* self, str key, u32 value) {
  if ((self->buckets.length == 0)) {
    List$1483$initialize(&self->buckets, 16);
  }
  u64 idx  = (str$hash(key) % self->buckets.length);
  {
    IterMut$1482 $iterator = List$1482$iter_mut(&(*(List$1483$subscript(&self->buckets, idx))));
    while (1) {
      auto $next = IterMut$1482$next(&$iterator);
      if (!$next.index != 1) break;
      $tuple18$5* pair = $next.Some.$0;
      {
        if ((str$eq(pair->$0, key))) {
          (pair->$1 = value);
          return;
        }
      }
    }
  }
  List$1482$push(&(*(List$1483$subscript(&self->buckets, idx))), ($tuple18$5) {.$0 = key, .$1 = value});
  (self->length += 1);
}
map$Map$18_5 map$Map$18_5$init(InitList$1482 init_list) {
  map$Map$18_5 self = {};
  {
    InitList$1482 $iterable = init_list;
    Iter$1482 $iterator = InitList$1482$iter(&$iterable);
    while (1) {
      auto $next = Iter$1482$next(&$iterator);
      if (!$next.index != 1) break;
      auto $deconstruction$0 = $next.Some.$0;
      auto key = $deconstruction$0.$0;
      auto value = $deconstruction$0.$1;
      {
        map$Map$18_5$insert(&self, key, value);
      }
    }
  }
  return self;
}
map$Map$18_5 lexer$operators() {
  return map$Map$18_5$init((InitList$1482){ .data = ($tuple18$5[]) {($tuple18$5) {.$0 = (str) { .data = ",", .length = 1 }, .$1 = lexer$TType$Comma}, ($tuple18$5) {.$0 = (str) { .data = ";", .length = 1 }, .$1 = lexer$TType$Semicolon}, ($tuple18$5) {.$0 = (str) { .data = "+", .length = 1 }, .$1 = lexer$TType$Add}, ($tuple18$5) {.$0 = (str) { .data = "-", .length = 1 }, .$1 = lexer$TType$Sub}, ($tuple18$5) {.$0 = (str) { .data = "/", .length = 1 }, .$1 = lexer$TType$Div}, ($tuple18$5) {.$0 = (str) { .data = "*", .length = 1 }, .$1 = lexer$TType$Mul}, ($tuple18$5) {.$0 = (str) { .data = "%", .length = 1 }, .$1 = lexer$TType$Modulo}, ($tuple18$5) {.$0 = (str) { .data = "=", .length = 1 }, .$1 = lexer$TType$Assign}, ($tuple18$5) {.$0 = (str) { .data = "(", .length = 1 }, .$1 = lexer$TType$OpenParen}, ($tuple18$5) {.$0 = (str) { .data = ")", .length = 1 }, .$1 = lexer$TType$CloseParen}, ($tuple18$5) {.$0 = (str) { .data = "{", .length = 1 }, .$1 = lexer$TType$OpenCurly}, ($tuple18$5) {.$0 = (str) { .data = "}", .length = 1 }, .$1 = lexer$TType$CloseCurly}}, .length = 12});
}
typedef struct $tuple1481 {
  map$Map$18_5 $0;
} $tuple1481;
typedef struct Option$1481 Option$1481;
typedef $tuple1481 Option$1481$Some;
typedef struct Option$1481 {
  int index;
  union {
    Option$1481$Some Some;
  };
} Option$1481;
Option$1481 Some$1481(map$Map$18_5 t) {
  return (Option$1481) {
.index = 0,
.Some = ($tuple1481) {.$0 = t}};
}
map$Map$18_5 lexer$keywords() {
  return map$Map$18_5$init((InitList$1482){ .data = ($tuple18$5[]) {($tuple18$5) {.$0 = (str) { .data = "extrn", .length = 5 }, .$1 = lexer$TType$Extrn}, ($tuple18$5) {.$0 = (str) { .data = "auto", .length = 4 }, .$1 = lexer$TType$Auto}, ($tuple18$5) {.$0 = (str) { .data = "if", .length = 2 }, .$1 = lexer$TType$If}}, .length = 3});
}
Option$1481 Some$1481(map$Map$18_5 t);
typedef struct $tuple1716 {
  List$18 $0;
} $tuple1716;
typedef struct Option$1716 Option$1716;
typedef $tuple1716 Option$1716$Some;
typedef struct Option$1716 {
  int index;
  union {
    Option$1716$Some Some;
  };
} Option$1716;
Option$1716 Some$1716(List$18 t) {
  return (Option$1716) {
.index = 0,
.Some = ($tuple1716) {.$0 = t}};
}
map$Map$18_5 Option$1481$or_else(Option$1481 self, map$Map$18_5 fallback) {
if (self.index == 0) {
map$Map$18_5 v = (self.Some.$0);
{
    return v;
  }
}
  else{
    return fallback;
  }
}
List$18 Option$1716$or_else(Option$1716 self, List$18 fallback) {
if (self.index == 0) {
List$18 v = (self.Some.$0);
{
    return v;
  }
}
  else{
    return fallback;
  }
}
typedef struct Slice$7 {
  u8* data;
  u64 length;
} Slice$7;
Slice$7 str$as_byte_slice(str self) {
  return (Slice$7){
    .data = (u8*)self.data,
    .length = (u64)self.length};
}
bool Slice$7$is_empty(Slice$7 self) {
  return (self.length == 0);
}
extern u8*  strdup(u8*);
String String$from$18(str data) {
  Slice$7 slice  = str$as_byte_slice(data);
  if (Slice$7$is_empty(slice)) {
    return (String){0};
  }
  return (String){
    .data = (u8*)strdup(slice.data),
    .capacity = (u64)slice.length,
    .length = (u64)slice.length};
}
elexify$Lexer elexify$Lexer$new(Option$1481 operators, Option$1481 keywords, Option$1716 reserved) {
  return (elexify$Lexer){
    .operators = (map$Map$18_5)Option$1481$or_else(operators, (map$Map$18_5){0}),
    .keywords = (map$Map$18_5)Option$1481$or_else(keywords, (map$Map$18_5){0}),
    .reserved = (List$18)Option$1716$or_else(reserved, (List$18){0}),
    .reserved_placeholder = (String)String$from$18((str) { .data = "$", .length = 1 })};
}
typedef struct elexify$State {
  String input;
  String path;
  u64 pos;
  u64 col;
  u64 line;
  u64 file_idx;
} elexify$State;
typedef struct $tuple19 {
  String $0;
} $tuple19;
typedef struct Option$19 Option$19;
typedef $tuple19 Option$19$Some;
typedef struct Option$19 {
  int index;
  union {
    Option$19$Some Some;
  };
} Option$19;
Option$19 None$1074() {
  return  (Option$19) { .index = 1};
}
extern u8*  realpath(u8*, u8*);
Option$19 None$1074();
String String$from_ptr(u8* data) {
  u32 length  = strlen(data);
  return (String){
    .data = (u8*)strdup(data),
    .capacity = (u64)length,
    .length = (u64)length};
}
Option$19 Some$19(String t) {
  return (Option$19) {
.index = 0,
.Some = ($tuple19) {.$0 = t}};
}
Option$19 fs$canonical_path$18(str path) {
  Slice$7 slice  = str$as_byte_slice(path);
  if ((slice.length == 0)) {
    return None$1074();
  }
  u8 resolved_path[4096] = {0};
  if ((!realpath(slice.data, resolved_path))) {
    return None$1074();
  }
  return Some$19(String$from_ptr(resolved_path));
}
bool Option$19$is_some(Option$19 self) {
if (self.index == 0) {
{
    return true;
  }
}
  return false;
}
bool Option$19$is_none(Option$19 self) {
  return (!Option$19$is_some(self));
}
typedef struct $tuple18 {
  str $0;
} $tuple18;
typedef struct fmt$FormatOptions {
  u8 digits_after_decimal;
  bool indented;
  bool quote_strings;
  bool enum_parent_name;
} fmt$FormatOptions;
typedef struct fmt$FormatOptions fmt$FormatOptions;
fmt$FormatOptions* fmt$FormatOptions$current() {
  static fmt$FormatOptions current  = (fmt$FormatOptions){
    .digits_after_decimal = (u8)2,
    .indented = (bool)false,
    .quote_strings = (bool)false,
    .enum_parent_name = (bool)true};
  return (&current);
}
typedef struct fmt$StringBuilderBlock fmt$StringBuilderBlock;
typedef struct fmt$StringBuilder {
  fmt$StringBuilderBlock* root;
  fmt$StringBuilderBlock* current;
} fmt$StringBuilder;
typedef struct fmt$StringBuilder fmt$StringBuilder;
typedef struct fmt$StringBuilderBlock {
  u8* data;
  u64 length;
  fmt$StringBuilderBlock* next;
} fmt$StringBuilderBlock;
void fmt$StringBuilderBlock$deinit(fmt$StringBuilderBlock* self);
void fmt$StringBuilderBlock$deinit(fmt$StringBuilderBlock* self) {
  if (self->data) {
    free(self->data);
  }
  if (self->next) {
    fmt$StringBuilderBlock$deinit(self->next);
    free(self->next);
  }
}
void fmt$StringBuilder$deinit(fmt$StringBuilder* self) {
  if (self->root) {
    fmt$StringBuilderBlock$deinit(self->root);
    free(self->root);
  }
}
typedef struct Field Field;
typedef struct List$37 {
  Field* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$37;
typedef struct $tuple18$213 $tuple18$213;
typedef struct List$548 {
  $tuple18$213* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$548;
typedef struct Type {
  s32 id;
  str name;
  u64 size;
  u64 flags;
  List$37 fields;
  Type* element_type;
  List$146 generic_args;
  List$146 interfaces;
  List$548 methods;
} Type;
bool List$37$is_empty(List$37 self) {
  return (self.length == 0);
}
String String$from$18(str data);
Slice$7 u32$as_byte_slice(u32 self) {
  static u8 chars[2] = {0x0, 0x0};
  (chars[0] = self);
  return (Slice$7){
    .data = (u8*)chars,
    .length = (u64)1};
}
static constexpr s32 fmt$STRING_BUILDER_BLOCK_MAX_LEN  = 8192;
fmt$StringBuilderBlock* fmt$StringBuilderBlock$new() {
  fmt$StringBuilderBlock* self  = malloc(sizeof(fmt$StringBuilderBlock));
  (self->data = calloc(fmt$STRING_BUILDER_BLOCK_MAX_LEN, sizeof(u8)));
  (self->length = 0);
  (self->next = NULL);
  return self;
}
void fmt$StringBuilder$append$5(fmt$StringBuilder* self, u32 value) {
  Slice$7 slice  = u32$as_byte_slice(value);
  if ((slice.length <= 0)) {
    return;
  }
  if ((!self->root)) {
    (self->root = fmt$StringBuilderBlock$new());
    (self->current = self->root);
  }
  s32 slice_index  = 0;
  u64 length  = slice.length;
  if (((length == 1) && (slice.data[0] == 0x0))) {
    return;
  }
  s32 remaining  = (fmt$STRING_BUILDER_BLOCK_MAX_LEN - self->current->length);
  while ((length > 0)) {
    if ((length <= remaining)) {
      memcpy((self->current->data + self->current->length), slice.data, length);
      (self->current->length += length);
      break;
    }
    if (((self->current->data != NULL) && (slice.data != NULL))) {
      memcpy((self->current->data + self->current->length), (slice.data + slice_index), remaining);
      (self->current->length += remaining);
    }
    (slice_index += remaining);
    (length -= remaining);
    (self->current->next = fmt$StringBuilderBlock$new());
    (self->current = self->current->next);
    (remaining = fmt$STRING_BUILDER_BLOCK_MAX_LEN);
  }
}
void(*panic_handler)(str)= {0};
extern s32  printf(u8*, ...);;
extern void  exit(s32);
void $lambda$4 (str msg)
{
  printf("panic(): %s\n", msg.data);
  exit(1);
}

void panic(str msg) {
  if ((!panic_handler)) {
    (panic_handler = $lambda$4);
  }
  panic_handler(msg);
}
typedef struct Field {
  str name;
  Type* type;
  u64 size;
  u64 offset;
  s64 enum_value;
} Field;
typedef struct List$37 List$37;
Field* List$37$subscript(List$37* self, u64 idx) {
  return (&self->data[idx]);
}
typedef struct any {
  void* ptr;
  Type* type;
} any;
typedef struct $tuple18 $tuple18;
u8* Field$get$685(Field* self, $tuple18* source) {
  return ((u8*)source + self->offset);
}
typedef struct Iter$146 {
  Type** ptr;
  Type** end;
} Iter$146;
typedef struct List$146 List$146;
Iter$146 List$146$iter(List$146* self) {
  return (Iter$146){
    .ptr = (Type**)self->data,
    .end = (Type**)(Type**)(self->data + self->length)};
}
typedef struct $tuple146 {
  Type* $0;
} $tuple146;
typedef struct Option$146 Option$146;
typedef $tuple146 Option$146$Some;
typedef struct Option$146 {
  int index;
  union {
    Option$146$Some Some;
  };
} Option$146;
typedef struct Iter$146 Iter$146;
Option$146 Iter$146$next(Iter$146* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$146) { .index = 1};
  }
  Option$146 value  = (Option$146) {
.index = 0,
.Some = ($tuple146) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
bool Type$implements(Type* self, str interface_name) {
  {
    List$146 $iterable = self->interfaces;
    Iter$146 $iterator = List$146$iter(&$iterable);
    while (1) {
      auto $next = Iter$146$next(&$iterator);
      if (!$next.index != 1) break;
      Type* iface = $next.Some.$0;
      {
        if ((str$eq(iface->name, interface_name))) {
          return true;
        }
      }
    }
  }
  return false;
}
typedef struct $tuple {
} $tuple;
typedef struct $tuple3649 {
  $tuple $0;
} $tuple3649;
typedef struct Option$3649 Option$3649;
typedef $tuple3649 Option$3649$Some;
typedef struct Option$3649 {
  int index;
  union {
    Option$3649$Some Some;
  };
} Option$3649;
typedef struct dyn$fmt$Format{
void *instance;
void(*format)(void*, fmt$StringBuilder*, fmt$FormatOptions);
} dyn$fmt$Format;
bool $lambda$6 ($tuple18$213* tuple)
{
  return (str$eq(tuple->$0, (str) { .data = "format", .length = 6 }));
}

$tuple18$213* List$548$find_first_of(List$548 self, bool(*finder)($tuple18$213*)) {
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = self.length};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 idx = $next.Some.$0;
      {
        if (finder((&self.data[idx]))) {
          return (&self.data[idx]);
        }
      }
    }
  }
  return NULL;
}
dyn$fmt$Format fmt$new_dyn_format(any value) {
any $deconstruction$0 = value;
auto instance = $deconstruction$0.ptr;
auto type = $deconstruction$0.type;
  $tuple18$213* tuple  = List$548$find_first_of(type->methods, $lambda$6);
  if ((!tuple)) {
    printf("unable to find 'format' in type %s\n", type->name);
    panic((str) { .data = "DynFormat failure", .length = 17 });
  }
$tuple18$213 $deconstruction$1 = (*tuple);
auto _ = $deconstruction$1.$0;
auto method = $deconstruction$1.$1;
  dyn$fmt$Format dynamic = {0};
  (dynamic.instance = instance);
  (dynamic.format = (void(*)(void*, fmt$StringBuilder*, fmt$FormatOptions))method);
  return dynamic;
}
void fmt$StringBuilder$append$18(fmt$StringBuilder* self, str value) {
  Slice$7 slice  = str$as_byte_slice(value);
  if ((slice.length <= 0)) {
    return;
  }
  if ((!self->root)) {
    (self->root = fmt$StringBuilderBlock$new());
    (self->current = self->root);
  }
  s32 slice_index  = 0;
  u64 length  = slice.length;
  if (((length == 1) && (slice.data[0] == 0x0))) {
    return;
  }
  s32 remaining  = (fmt$STRING_BUILDER_BLOCK_MAX_LEN - self->current->length);
  while ((length > 0)) {
    if ((length <= remaining)) {
      memcpy((self->current->data + self->current->length), slice.data, length);
      (self->current->length += length);
      break;
    }
    if (((self->current->data != NULL) && (slice.data != NULL))) {
      memcpy((self->current->data + self->current->length), (slice.data + slice_index), remaining);
      (self->current->length += remaining);
    }
    (slice_index += remaining);
    (length -= remaining);
    (self->current->next = fmt$StringBuilderBlock$new());
    (self->current = self->current->next);
    (remaining = fmt$STRING_BUILDER_BLOCK_MAX_LEN);
  }
}
typedef struct String String;
Slice$7 String$as_byte_slice(String self) {
  return (Slice$7){
    .data = (u8*)self.data,
    .length = (u64)self.length};
}
void fmt$StringBuilder$append$19(fmt$StringBuilder* self, String value) {
  Slice$7 slice  = String$as_byte_slice(value);
  if ((slice.length <= 0)) {
    return;
  }
  if ((!self->root)) {
    (self->root = fmt$StringBuilderBlock$new());
    (self->current = self->root);
  }
  s32 slice_index  = 0;
  u64 length  = slice.length;
  if (((length == 1) && (slice.data[0] == 0x0))) {
    return;
  }
  s32 remaining  = (fmt$STRING_BUILDER_BLOCK_MAX_LEN - self->current->length);
  while ((length > 0)) {
    if ((length <= remaining)) {
      memcpy((self->current->data + self->current->length), slice.data, length);
      (self->current->length += length);
      break;
    }
    if (((self->current->data != NULL) && (slice.data != NULL))) {
      memcpy((self->current->data + self->current->length), (slice.data + slice_index), remaining);
      (self->current->length += remaining);
    }
    (slice_index += remaining);
    (length -= remaining);
    (self->current->next = fmt$StringBuilderBlock$new());
    (self->current = self->current->next);
    (remaining = fmt$STRING_BUILDER_BLOCK_MAX_LEN);
  }
}
void fmt$StringBuilder$append$18(fmt$StringBuilder* self, str value);
typedef enum {
  TypeFlags$INTEGER = 1,
  TypeFlags$FLOAT = 2,
  TypeFlags$BOOL = 4,
  TypeFlags$STRING = 8,
  TypeFlags$STRUCT = 16,
  TypeFlags$CHOICE = 32,
  TypeFlags$ENUM = 64,
  TypeFlags$TUPLE = 128,
  TypeFlags$ARRAY = 256,
  TypeFlags$FUNCTION = 512,
  TypeFlags$POINTER = 1024,
  TypeFlags$SIGNED = 2048,
  TypeFlags$UNSIGNED = 4096,
  TypeFlags$INTERFACE = 8192,
  TypeFlags$UNION = 16384
} TypeFlags;
bool Type$is_pointer(Type* self) {
  return ((self->flags & TypeFlags$POINTER) != 0);
}
bool Type$is_bool(Type* self) {
  return ((self->flags & TypeFlags$BOOL) != 0);
}
void* Dyn_Allocator$copy(Dyn_Allocator* self, void* ptr, u64 element_size, u64 n) {
  void*(*p_copy)(void*, void*, u64, u64) = self->p_copy;
  return p_copy(self->instance, ptr, element_size, n);
}
String str$to_string$34(str self, Dyn_Allocator* allocator) {
  return (String){
    .data = (u8*)Dyn_Allocator$copy(allocator, self.data, sizeof(u8), self.length),
    .length = (u64)self.length};
}
String str$to_string$34(str self, Dyn_Allocator* allocator);
bool Type$is_enum(Type* self) {
  return ((self->flags & TypeFlags$ENUM) != 0);
}
typedef struct Iter$37 {
  Field* ptr;
  Field* end;
} Iter$37;
Iter$37 List$37$iter(List$37* self) {
  return (Iter$37){
    .ptr = (Field*)self->data,
    .end = (Field*)(Field*)(self->data + self->length)};
}
typedef struct $tuple37 {
  Field $0;
} $tuple37;
typedef struct Option$37 Option$37;
typedef $tuple37 Option$37$Some;
typedef struct Option$37 {
  int index;
  union {
    Option$37$Some Some;
  };
} Option$37;
typedef struct Iter$37 Iter$37;
Option$37 Iter$37$next(Iter$37* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$37) { .index = 1};
  }
  Option$37 value  = (Option$37) {
.index = 0,
.Some = ($tuple37) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
bool Type$is_signed(Type* self) {
  return ((self->flags & TypeFlags$SIGNED) != 0);
}
bool Type$is_unsigned(Type* self) {
  return ((self->flags & TypeFlags$UNSIGNED) != 0);
}
extern s32  sprintf(u8*, u8*, ...);;
extern s32  snprintf(u8*, u64, u8*, ...);;
String fmt$to_string$152(void* value) {
  Type* type  = _type_info.data[152];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$0;
    auto $switch_target$0 = type;
    if ($switch_target$0 == _type_info.data[2]) {
$register$0 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$0 == _type_info.data[1]) {
$register$0 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$0 == _type_info.data[0]) {
$register$0 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$0 == _type_info.data[7]) {
$register$0 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$0 == _type_info.data[6]) {
$register$0 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$0 == _type_info.data[5]) {
$register$0 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$0 == _type_info.data[4]) {
$register$0 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$0;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
void Dyn_Allocator$free(Dyn_Allocator* self, void* ptr) {
  void(*p_free)(void*, void*) = self->p_free;
  p_free(self->instance, ptr);
}
void String$deinit(String* self) {
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  Dyn_Allocator$free(self->allocator, self->data);
  (self->data = NULL);
  (self->capacity = 0);
  (self->length = 0);
}
void fmt$StringBuilder$append_then_free$19(fmt$StringBuilder* self, String value) {
  fmt$StringBuilder$append$19(self, value);
  String$deinit(&value);
}
bool Type$is_struct(Type* self) {
  return ((self->flags & TypeFlags$STRUCT) != 0);
}
u8* Field$get$11(Field* self, void* source) {
  return ((u8*)source + self->offset);
}
void fmt$format_any(any value, fmt$StringBuilder* builder, fmt$FormatOptions options);
void fmt$format_struct(any value, fmt$StringBuilder* builder, fmt$FormatOptions options) {
  fmt$StringBuilder$append$18(builder, value.type->name);
  fmt$StringBuilder$append$18(builder, (str) { .data = " {", .length = 2 });
  if (options.indented) {
    fmt$StringBuilder$append$18(builder, (str) { .data = "\n", .length = 1 });
  }
  s32 idx  = 0;
  {
    List$37 $iterable = value.type->fields;
    Iter$37 $iterator = List$37$iter(&$iterable);
    while (1) {
      auto $next = Iter$37$next(&$iterator);
      if (!$next.index != 1) break;
      Field field = $next.Some.$0;
      {
        if (options.indented) {
          fmt$StringBuilder$append$18(builder, (str) { .data = "  ", .length = 2 });
        }
        fmt$StringBuilder$append$18(builder, (str) { .data = " ", .length = 1 });
        fmt$StringBuilder$append$18(builder, field.name);
        fmt$StringBuilder$append$18(builder, (str) { .data = ": ", .length = 2 });
        fmt$format_any((any){
          .type = (Type*)field.type,
          .ptr = (void*)Field$get$11(&field, value.ptr)}, builder, options);
        if ((idx != (value.type->fields.length - 1))) {
          fmt$StringBuilder$append$18(builder, (str) { .data = ",", .length = 1 });
        }
        if (options.indented) {
          fmt$StringBuilder$append$18(builder, (str) { .data = "\n", .length = 1 });
        }
        idx++;
      }
    }
  }
  if ((!options.indented)) {
    fmt$StringBuilder$append$18(builder, (str) { .data = " }", .length = 2 });
  }
  else{
    fmt$StringBuilder$append$18(builder, (str) { .data = "}", .length = 1 });
  }
}
bool Type$is_tuple(Type* self) {
  return ((self->flags & TypeFlags$TUPLE) != 0);
}
u8* Field$get$11(Field* self, void* source);
void fmt$format_tuple(any value, fmt$StringBuilder* builder, fmt$FormatOptions options) {
  fmt$StringBuilder$append$18(builder, (str) { .data = "(", .length = 1 });
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = value.type->fields.length};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 i = $next.Some.$0;
      {
        Field field  = (*(List$37$subscript(&value.type->fields, i)));
        fmt$format_any((any){
          .type = (Type*)field.type,
          .ptr = (void*)Field$get$11(&field, value.ptr)}, builder, options);
        if ((i != (value.type->fields.length - 1))) {
          fmt$StringBuilder$append$18(builder, (str) { .data = ", ", .length = 2 });
        }
      }
    }
  }
  fmt$StringBuilder$append$18(builder, (str) { .data = ")", .length = 1 });
}
typedef struct any any;
u8* any$unwrap$150(any* self) {
  return (*(u8**)self->ptr);
}
s32 any$unwrap$1(any* self) {
  return (*(s32*)self->ptr);
}
u8 any$unwrap$7(any* self) {
  return (*(u8*)self->ptr);
}
String fmt$to_string$7(u8 value) {
  Type* type  = _type_info.data[7];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$1;
    auto $switch_target$1 = type;
    if ($switch_target$1 == _type_info.data[2]) {
$register$1 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$1 == _type_info.data[1]) {
$register$1 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$1 == _type_info.data[0]) {
$register$1 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$1 == _type_info.data[7]) {
$register$1 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$1 == _type_info.data[6]) {
$register$1 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$1 == _type_info.data[5]) {
$register$1 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$1 == _type_info.data[4]) {
$register$1 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$1;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
void fmt$StringBuilder$append_then_free$19(fmt$StringBuilder* self, String value);
u16 any$unwrap$6(any* self) {
  return (*(u16*)self->ptr);
}
String fmt$to_string$6(u16 value) {
  Type* type  = _type_info.data[6];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$2;
    auto $switch_target$2 = type;
    if ($switch_target$2 == _type_info.data[2]) {
$register$2 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$2 == _type_info.data[1]) {
$register$2 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$2 == _type_info.data[0]) {
$register$2 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$2 == _type_info.data[7]) {
$register$2 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$2 == _type_info.data[6]) {
$register$2 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$2 == _type_info.data[5]) {
$register$2 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$2 == _type_info.data[4]) {
$register$2 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$2;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
u32 any$unwrap$5(any* self) {
  return (*(u32*)self->ptr);
}
String fmt$to_string$5(u32 value) {
  Type* type  = _type_info.data[5];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$3;
    auto $switch_target$3 = type;
    if ($switch_target$3 == _type_info.data[2]) {
$register$3 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$3 == _type_info.data[1]) {
$register$3 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$3 == _type_info.data[0]) {
$register$3 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$3 == _type_info.data[7]) {
$register$3 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$3 == _type_info.data[6]) {
$register$3 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$3 == _type_info.data[5]) {
$register$3 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$3 == _type_info.data[4]) {
$register$3 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$3;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
u64 any$unwrap$4(any* self) {
  return (*(u64*)self->ptr);
}
String fmt$to_string$4(u64 value) {
  Type* type  = _type_info.data[4];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$4;
    auto $switch_target$4 = type;
    if ($switch_target$4 == _type_info.data[2]) {
$register$4 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$4 == _type_info.data[1]) {
$register$4 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$4 == _type_info.data[0]) {
$register$4 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$4 == _type_info.data[7]) {
$register$4 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$4 == _type_info.data[6]) {
$register$4 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$4 == _type_info.data[5]) {
$register$4 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$4 == _type_info.data[4]) {
$register$4 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$4;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
s8 any$unwrap$3(any* self) {
  return (*(s8*)self->ptr);
}
String fmt$to_string$3(s8 value) {
  Type* type  = _type_info.data[3];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$5;
    auto $switch_target$5 = type;
    if ($switch_target$5 == _type_info.data[2]) {
$register$5 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$5 == _type_info.data[1]) {
$register$5 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$5 == _type_info.data[0]) {
$register$5 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$5 == _type_info.data[7]) {
$register$5 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$5 == _type_info.data[6]) {
$register$5 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$5 == _type_info.data[5]) {
$register$5 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$5 == _type_info.data[4]) {
$register$5 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$5;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
s16 any$unwrap$2(any* self) {
  return (*(s16*)self->ptr);
}
String fmt$to_string$2(s16 value) {
  Type* type  = _type_info.data[2];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$6;
    auto $switch_target$6 = type;
    if ($switch_target$6 == _type_info.data[2]) {
$register$6 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$6 == _type_info.data[1]) {
$register$6 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$6 == _type_info.data[0]) {
$register$6 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$6 == _type_info.data[7]) {
$register$6 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$6 == _type_info.data[6]) {
$register$6 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$6 == _type_info.data[5]) {
$register$6 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$6 == _type_info.data[4]) {
$register$6 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$6;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
s32 any$unwrap$1(any* self);
String fmt$to_string$1(s32 value) {
  Type* type  = _type_info.data[1];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$7;
    auto $switch_target$7 = type;
    if ($switch_target$7 == _type_info.data[2]) {
$register$7 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$7 == _type_info.data[1]) {
$register$7 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$7 == _type_info.data[0]) {
$register$7 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$7 == _type_info.data[7]) {
$register$7 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$7 == _type_info.data[6]) {
$register$7 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$7 == _type_info.data[5]) {
$register$7 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$7 == _type_info.data[4]) {
$register$7 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$7;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
s64 any$unwrap$0(any* self) {
  return (*(s64*)self->ptr);
}
String fmt$to_string$0(s64 value) {
  Type* type  = _type_info.data[0];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$8;
    auto $switch_target$8 = type;
    if ($switch_target$8 == _type_info.data[2]) {
$register$8 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$8 == _type_info.data[1]) {
$register$8 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$8 == _type_info.data[0]) {
$register$8 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$8 == _type_info.data[7]) {
$register$8 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$8 == _type_info.data[6]) {
$register$8 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$8 == _type_info.data[5]) {
$register$8 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$8 == _type_info.data[4]) {
$register$8 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$8;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
f32 any$unwrap$9(any* self) {
  return (*(f32*)self->ptr);
}
String fmt$to_string$9(f32 value) {
  Type* type  = _type_info.data[9];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$9;
    auto $switch_target$9 = type;
    if ($switch_target$9 == _type_info.data[2]) {
$register$9 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$9 == _type_info.data[1]) {
$register$9 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$9 == _type_info.data[0]) {
$register$9 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$9 == _type_info.data[7]) {
$register$9 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$9 == _type_info.data[6]) {
$register$9 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$9 == _type_info.data[5]) {
$register$9 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$9 == _type_info.data[4]) {
$register$9 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$9;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
f64 any$unwrap$8(any* self) {
  return (*(f64*)self->ptr);
}
String fmt$to_string$8(f64 value) {
  Type* type  = _type_info.data[8];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$10;
    auto $switch_target$10 = type;
    if ($switch_target$10 == _type_info.data[2]) {
$register$10 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$10 == _type_info.data[1]) {
$register$10 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$10 == _type_info.data[0]) {
$register$10 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$10 == _type_info.data[7]) {
$register$10 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$10 == _type_info.data[6]) {
$register$10 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$10 == _type_info.data[5]) {
$register$10 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$10 == _type_info.data[4]) {
$register$10 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$10;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
bool any$unwrap$10(any* self) {
  return (*(bool*)self->ptr);
}
String fmt$to_string$10(bool value) {
  Type* type  = _type_info.data[10];
  str format = {};
  if (Type$is_bool(type)) {
    if (value) {
      return str$to_string$34((str) { .data = "true", .length = 4 }, get_default_allocator());
    }
    else{
      return str$to_string$34((str) { .data = "false", .length = 5 }, get_default_allocator());
    }
  }
  if (Type$is_enum(type)) {
    {
      List$37 $iterable = type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((value == field.enum_value)) {
            return String$from$18(field.name);
          }
        }
      }
    }
  }
  u8 format_buffer[255] = {0};
  if (Type$is_pointer(type)) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x70);
    (format_buffer[2] = 0x0);
  }
  else
  if ((type == _type_info.data[7])) {
    (format_buffer[0] = 0x25);
    (format_buffer[1] = 0x63);
    (format_buffer[2] = 0x0);
  }
  else
  if ((Type$is_signed(type) || Type$is_unsigned(type))) {
        str $register$11;
    auto $switch_target$11 = type;
    if ($switch_target$11 == _type_info.data[2]) {
$register$11 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$11 == _type_info.data[1]) {
$register$11 = (str) { .data = "%d", .length = 2 };
    }
    else     if ($switch_target$11 == _type_info.data[0]) {
$register$11 = (str) { .data = "%ld", .length = 3 };
    }
    else     if ($switch_target$11 == _type_info.data[7]) {
$register$11 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$11 == _type_info.data[6]) {
$register$11 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$11 == _type_info.data[5]) {
$register$11 = (str) { .data = "%u", .length = 2 };
    }
    else     if ($switch_target$11 == _type_info.data[4]) {
$register$11 = (str) { .data = "%lu", .length = 3 };
    }
    str string = $register$11;
    s32 i  = 0;
    {
      str $iterable = string;
      Iter$7 $iterator = str$iter(&$iterable);
      while (1) {
        auto $next = Iter$7$next(&$iterator);
        if (!$next.index != 1) break;
        u8 ch = $next.Some.$0;
        {
          (format_buffer[i] = ch);
          i++;
        }
      }
    }
  }
  else
  if ((type == _type_info.data[9])) {
    sprintf(format_buffer, "%%.%df", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else
  if ((type == _type_info.data[8])) {
    sprintf(format_buffer, "%%.%dlf", fmt$FormatOptions$current()->digits_after_decimal);
  }
  else{
    return (String){0};
  }
  u8 buffer[1024] = {0};
  snprintf(buffer, (1024 * sizeof(u8)), format_buffer, value);
  return String$from_ptr(buffer);
}
void fmt$format_any(any value, fmt$StringBuilder* builder, fmt$FormatOptions options) {
  if (Type$implements(value.type, (str) { .data = "Format", .length = 6 })) {
    dyn$fmt$Format dyn_format  = fmt$new_dyn_format(value);
    dyn_format.format(dyn_format.instance, builder, options);
    return;
  }
  if ((value.type == _type_info.data[19])) {
    if (options.quote_strings) {
      fmt$StringBuilder$append$18(builder, (str) { .data = "\"", .length = 1 });
    }
    fmt$StringBuilder$append$19(builder, (*(String*)value.ptr));
    if (options.quote_strings) {
      fmt$StringBuilder$append$18(builder, (str) { .data = "\"", .length = 1 });
    }
  }
  else
  if ((value.type == _type_info.data[18])) {
    if (options.quote_strings) {
      fmt$StringBuilder$append$18(builder, (str) { .data = "\"", .length = 1 });
    }
    fmt$StringBuilder$append$18(builder, (*(str*)value.ptr));
    if (options.quote_strings) {
      fmt$StringBuilder$append$18(builder, (str) { .data = "\"", .length = 1 });
    }
  }
  else
  if (Type$is_pointer(value.type)) {
    fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$152(value.ptr));
  }
  else
  if (Type$is_struct(value.type)) {
    fmt$format_struct(value, builder, options);
  }
  else
  if (Type$is_tuple(value.type)) {
    fmt$format_tuple(value, builder, options);
  }
  else
  if ((value.ptr == NULL)) {
    fmt$StringBuilder$append$18(builder, (str) { .data = "null", .length = 4 });
  }
  else
  if ((value.type == _type_info.data[150])) {
    fmt$StringBuilder$append$19(builder, String$from_ptr(any$unwrap$150(&value)));
  }
  else
  if (Type$is_enum(value.type)) {
    if (options.enum_parent_name) {
      fmt$StringBuilder$append$18(builder, value.type->name);
      fmt$StringBuilder$append$18(builder, (str) { .data = "::", .length = 2 });
    }
    {
      List$37 $iterable = value.type->fields;
      Iter$37 $iterator = List$37$iter(&$iterable);
      while (1) {
        auto $next = Iter$37$next(&$iterator);
        if (!$next.index != 1) break;
        Field field = $next.Some.$0;
        {
          if ((field.enum_value == any$unwrap$1(&value))) {
            fmt$StringBuilder$append$18(builder, field.name);
            return;
          }
        }
      }
    }
    fmt$StringBuilder$append$18(builder, (str) { .data = "(invalid enum value)", .length = 20 });
  }
  else{
        auto $switch_target$12 = value.type;
    if ($switch_target$12 == _type_info.data[7]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$7(any$unwrap$7(&value)));
    }
    else     if ($switch_target$12 == _type_info.data[6]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$6(any$unwrap$6(&value)));
    }
    else     if ($switch_target$12 == _type_info.data[5]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$5(any$unwrap$5(&value)));
    }
    else     if ($switch_target$12 == _type_info.data[4]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$4(any$unwrap$4(&value)));
    }
    else     if ($switch_target$12 == _type_info.data[3]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$3(any$unwrap$3(&value)));
    }
    else     if ($switch_target$12 == _type_info.data[2]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$2(any$unwrap$2(&value)));
    }
    else     if ($switch_target$12 == _type_info.data[1]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$1(any$unwrap$1(&value)));
    }
    else     if ($switch_target$12 == _type_info.data[0]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$0(any$unwrap$0(&value)));
    }
    else     if ($switch_target$12 == _type_info.data[9]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$9(any$unwrap$9(&value)));
    }
    else     if ($switch_target$12 == _type_info.data[8]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$8(any$unwrap$8(&value)));
    }
    else     if ($switch_target$12 == _type_info.data[10]) {
      fmt$StringBuilder$append_then_free$19(builder, fmt$to_string$10(any$unwrap$10(&value)));
    }
else {
{
      fmt$StringBuilder$append$18(builder, (str) { .data = "(unsupported)", .length = 13 });
    }
}
;
  }
}
u64 fmt$StringBuilder$length(fmt$StringBuilder* self) {
  if ((!self->root)) {
    return 0;
  }
  fmt$StringBuilderBlock* current  = self->root;
  u64 len = {0};
  while (current) {
    (len += current->length);
    (current = current->next);
  }
  return len;
}
String fmt$StringBuilder$get_string(fmt$StringBuilder* self) {
  u64 length  = fmt$StringBuilder$length(self);
  u8* data  = malloc(((sizeof(u8) * length) + 1));
  (data[length] = 0x0);
  fmt$StringBuilderBlock* current  = self->root;
  s32 offset  = 0;
  while (current) {
    memcpy((data + offset), current->data, current->length);
    (offset += current->length);
    (current = current->next);
  }
  return (String){
    .data = (u8*)data,
    .length = (u64)length};
}
String fmt$format$685(str fmt, $tuple18 tuple, fmt$FormatOptions options) {
  if ((fmt.length == 0)) {
    String $defer$return$value = (String){0};
    return $defer$return$value;
  }
  fmt$StringBuilder builder = {};
  s32 value_index  = 0;
  List$37 fields  = _type_info.data[685]->fields;
  if (List$37$is_empty(fields)) {
    return String$from$18((str) { .data = "()", .length = 2 });
  }
  while ((*fmt.data)) {
    if ((((*fmt.data) == 0x5c) && ((*(fmt.data + 1)) == 0x25))) {
      fmt$StringBuilder$append$5(&builder, 0x25);
      (fmt.data += 2);
      continue;
    }
    if ((((*fmt.data) == 0x25) && (value_index >= fields.length))) {
      panic((str) { .data = "too few data arguments provided to 'format'", .length = 43 });
    }
    if ((((*fmt.data) == 0x25) && (value_index < fields.length))) {
      Field field  = (*(List$37$subscript(&fields, value_index)));
      any value  = (any){
        .type = (Type*)field.type,
        .ptr = (void*)Field$get$685(&field, (&tuple))};
      fmt$format_any(value, (&builder), options);
      value_index++;
    }
    else{
      fmt$StringBuilder$append$5(&builder, (u32)(*fmt.data));
    }
    fmt.data++;
  }
  String $defer$return$value = fmt$StringBuilder$get_string(&builder);
  fmt$StringBuilder$deinit(&builder);
  return $defer$return$value;
  fmt$StringBuilder$deinit(&builder);
}
void fmt$printlnf$685(str fmt, $tuple18 tuple) {
  String formatted  = fmt$format$685(fmt, tuple, (*fmt$FormatOptions$current()));
  printf("%s\n", formatted.data);
  String$deinit(&formatted);
}
String Option$19$unwrap(Option$19 self) {
    auto $switch_target$13 = self;
if ($switch_target$13.index == 0) {
String v = ($switch_target$13.Some.$0);
{
    return v;
  }
}
else {
{
    panic((str) { .data = "unwrapped a 'none' option", .length = 25 });
  }
}
;
  String $default = {};
  return $default;
}
extern u8*  dirname(u8*);
Option$19 fs$parent_path$19(String path) {
  Slice$7 slice  = String$as_byte_slice(path);
  if ((slice.length == 0)) {
    return None$1074();
  }
  u8* data  = strdup(slice.data);
  u8* name  = dirname(data);
  if ((!name)) {
    return None$1074();
  }
  Option$19 $defer$return$value = Some$19(String$from_ptr(name));
  free(data);
  return $defer$return$value;
  free(data);
}
Option$3649 None$3650() {
  return  (Option$3649) { .index = 1};
}
extern s32  chdir(u8*);
Option$3649 Some$3649($tuple t) {
  return (Option$3649) {
.index = 0,
.Some = ($tuple3649) {.$0 = t}};
}
Option$3649 fs$change_directory$19(String path) {
  Slice$7 slice  = String$as_byte_slice(path);
  if ((slice.length == 0)) {
    return None$3650();
  }
  if ((chdir(slice.data) != 0)) {
    return None$3650();
  }
  return Some$3649(($tuple) {});
}
$tuple Option$3649$unwrap(Option$3649 self) {
    auto $switch_target$14 = self;
if ($switch_target$14.index == 0) {
$tuple v = ($switch_target$14.Some.$0);
{
    return v;
  }
}
else {
{
    panic((str) { .data = "unwrapped a 'none' option", .length = 25 });
  }
}
;
  $tuple $default = {0};
  return $default;
}
typedef struct Result$19_18 {
  union {
    str err;
    String ok;
  };
  u8 index;
} Result$19_18;
typedef struct fs$_IO_FILE fs$_IO_FILE;
typedef struct fs$File {
  fs$_IO_FILE* fd;
} fs$File;
extern fs$_IO_FILE*  fopen(u8*, u8*);
u8 RESULT_IS_ERR  = 0;
Result$19_18 Result$19_18$Err(str v) {
  return (Result$19_18){
    .index = (u8)RESULT_IS_ERR,
    .err = (str)v};
}
void String$resize(String* self, u64 new_size) {
  if ((new_size < self->length)) {
    (self->length = new_size);
  }
  (self->capacity = new_size);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(u8), (new_size + 1)));
  (self->data[self->length] = 0);
}
extern s8  fgetc(fs$_IO_FILE*);
static constexpr s32 fs$EOF  = (s32)(-1);
void String$push(String* self, u8 ch) {
  if ((self->capacity == 0)) {
    (self->capacity = (256 / 3));
  }
  if (((!self->data) || ((self->length + 1) >= self->capacity))) {
    String$resize(self, ((self->capacity * 3) + 1));
  }
  (self->data[self->length] = ch);
  self->length++;
  (self->data[self->length] = 0x0);
}
extern void  fclose(fs$_IO_FILE*);
u8 RESULT_IS_OK  = 1;
Result$19_18 Result$19_18$Ok(String v) {
  return (Result$19_18){
    .index = (u8)RESULT_IS_OK,
    .ok = (String)v};
}
Result$19_18 fs$File$read_all$19(String filename_path) {
  Slice$7 filename  = String$as_byte_slice(filename_path);
  fs$_IO_FILE* file  = fopen(filename.data, "r");
  if ((!file)) {
    return Result$19_18$Err((str) { .data = "Couldnt open file", .length = 17 });
  }
  String string = {};
  String$resize(&string, 1024);
  while (true) {
    s8 c  = fgetc(file);
    if ((c == fs$EOF)) {
      break;
    }
    String$push(&string, c);
  }
  fclose(file);
  return Result$19_18$Ok(string);
}
String Result$19_18$unwrap(Result$19_18 self) {
  if ((self.index == RESULT_IS_ERR)) {
    panic((str) { .data = "called 'unwrap' on an Err result", .length = 32 });
  }
  return self.ok;
}
typedef struct Iter$19 {
  String* ptr;
  String* end;
} Iter$19;
typedef struct List$19 {
  String* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$19;
typedef struct elexify$SourceLocation {
  u64 line;
  u64 column;
  u64 file;
} elexify$SourceLocation;
typedef struct List$19 List$19;
static List$19* elexify$SourceLocation$files() {
  static List$19 files = {};
  return (&files);
}
Iter$19 List$19$iter(List$19* self) {
  return (Iter$19){
    .ptr = (String*)self->data,
    .end = (String*)(String*)(self->data + self->length)};
}
typedef struct Iter$19 Iter$19;
Option$19 Iter$19$next(Iter$19* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$19) { .index = 1};
  }
  Option$19 value  = (Option$19) {
.index = 0,
.Some = ($tuple19) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
u8* String$subscript(String* self, u64 idx) {
  return (&self->data[idx]);
}
bool String$eq(String self, String other) {
  if ((self.length != other.length)) {
    return false;
  }
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = self.length};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 idx = $next.Some.$0;
      {
        if (((*(String$subscript(&self, idx))) != (*(String$subscript(&other, idx))))) {
          return false;
        }
      }
    }
  }
  return true;
}
void List$19$resize(List$19* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(String), self->capacity));
}
void List$19$push(List$19* self, String v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$19$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
elexify$State elexify$State$new(String path, String input, u64 file_idx) {
  return (elexify$State){
    .path = (String)path,
    .input = (String)input,
    .file_idx = (u64)file_idx,
    .pos = (u64)0,
    .col = (u64)1,
    .line = (u64)1};
}
elexify$State elexify$State$from_file$18(str filename) {
  Option$19 canonical_option  = fs$canonical_path$18(filename);
  if (Option$19$is_none(canonical_option)) {
    fmt$printlnf$685((str) { .data = "file '%' was unable to be located.", .length = 34 }, ($tuple18) {.$0 = filename});
  }
  String canonical  = Option$19$unwrap(canonical_option);
  String parent  = Option$19$unwrap(fs$parent_path$19(canonical));
  Option$3649$unwrap(fs$change_directory$19(parent));
  String input  = Result$19_18$unwrap(fs$File$read_all$19(canonical));
  bool found  = false;
  s32 file_idx  = 0;
  {
    List$19 $iterable = (*elexify$SourceLocation$files());
    Iter$19 $iterator = List$19$iter(&$iterable);
    while (1) {
      auto $next = Iter$19$next(&$iterator);
      if (!$next.index != 1) break;
      String file = $next.Some.$0;
      {
        if ((String$eq(file, canonical))) {
          (found = true);
          break;
        }
        file_idx++;
      }
    }
  }
  if ((!found)) {
    List$19$push(elexify$SourceLocation$files(), canonical);
  }
  return elexify$State$new(canonical, input, file_idx);
}
typedef struct elexify$Lexer elexify$Lexer;
typedef struct List$59 List$59;
void List$59$resize(List$59* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(elexify$State), self->capacity));
}
void List$59$push(List$59* self, elexify$State v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$59$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
void elexify$Lexer$push_state(elexify$Lexer* self, elexify$State state) {
  List$59$push(&self->states, state);
}
typedef struct parser$Function parser$Function;
typedef struct List$138 {
  parser$Function* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$138;
typedef struct parser$Scope parser$Scope;
typedef struct $tuple3003 {
  parser$Scope* $0;
} $tuple3003;
typedef struct Option$3003 Option$3003;
typedef $tuple3003 Option$3003$Some;
typedef struct Option$3003 {
  int index;
  union {
    Option$3003$Some Some;
  };
} Option$3003;
typedef struct List$3016 List$3016;
typedef struct List$3017 {
  List$3016* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$3017;
typedef struct map$Map$1171_137 {
  List$3017 buckets;
  u64 length;
} map$Map$1171_137;
typedef struct parser$Scope {
  Option$3003 parent;
  map$Map$1171_137 variables;
} parser$Scope;
typedef struct parser$Program {
  List$138 functions;
  parser$Scope scope;
} parser$Program;
typedef struct interned$Interned$19 {
  String* data;
} interned$Interned$19;
typedef struct $tuple1171 {
  interned$Interned$19 $0;
} $tuple1171;
typedef struct Option$1171 Option$1171;
typedef $tuple1171 Option$1171$Some;
typedef struct Option$1171 {
  int index;
  union {
    Option$1171$Some Some;
  };
} Option$1171;
typedef struct elexify$Token {
  Option$1171 value;
  u32 type;
  elexify$SourceLocation location;
} elexify$Token;
bool List$59$is_empty(List$59 self) {
  return (self.length == 0);
}
elexify$Token elexify$Token$Eof() {
  static elexify$Token eof  = (elexify$Token){
    .type = (u32)elexify$TOKEN_EOF};
  return eof;
}
typedef struct List$58 List$58;
void List$58$resize(List$58* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(elexify$Token), self->capacity));
}
void List$58$push(List$58* self, elexify$Token v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$58$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
typedef struct $tuple1794 {
  elexify$State* $0;
} $tuple1794;
typedef struct Option$1794 Option$1794;
typedef $tuple1794 Option$1794$Some;
typedef struct Option$1794 {
  int index;
  union {
    Option$1794$Some Some;
  };
} Option$1794;
Option$1794 Some$1794(elexify$State* t) {
  return (Option$1794) {
.index = 0,
.Some = ($tuple1794) {.$0 = t}};
}
Option$1794 None$1825() {
  return  (Option$1794) { .index = 1};
}
Option$1794 List$59$back_mut(List$59* self) {
  if ((self->length > 0)) {
    return Some$1794((&self->data[(self->length - 1)]));
  }
  return None$1825();
}
elexify$State* Option$1794$unwrap(Option$1794 self) {
    auto $switch_target$15 = self;
if ($switch_target$15.index == 0) {
elexify$State* v = ($switch_target$15.Some.$0);
{
    return v;
  }
}
else {
{
    panic((str) { .data = "unwrapped a 'none' option", .length = 25 });
  }
}
;
  elexify$State* $default = {};
  return $default;
}
void fmt$StringBuilder$clear(fmt$StringBuilder* self) {
  fmt$StringBuilder$deinit(self);
}
extern s32  isxdigit(s32);
fmt$FormatOptions fmt$FormatOptions$$default() {
  return (fmt$FormatOptions){
    .digits_after_decimal = (u8)2,
    .indented = (bool)false,
    .quote_strings = (bool)false,
    .enum_parent_name = (bool)true};
}
typedef struct elexify$SourceLocation elexify$SourceLocation;
String* List$19$subscript(List$19* self, u64 idx) {
  return (&self->data[idx]);
}
typedef struct $tuple19$4$4 {
  String $0;
  u64 $1;
  u64 $2;
} $tuple19$4$4;
typedef struct $tuple19$4$4 $tuple19$4$4;
u8* Field$get$1451(Field* self, $tuple19$4$4* source) {
  return ((u8*)source + self->offset);
}
String fmt$format$1451(str fmt, $tuple19$4$4 tuple, fmt$FormatOptions options) {
  if ((fmt.length == 0)) {
    String $defer$return$value = (String){0};
    return $defer$return$value;
  }
  fmt$StringBuilder builder = {};
  s32 value_index  = 0;
  List$37 fields  = _type_info.data[1451]->fields;
  if (List$37$is_empty(fields)) {
    return String$from$18((str) { .data = "()", .length = 2 });
  }
  while ((*fmt.data)) {
    if ((((*fmt.data) == 0x5c) && ((*(fmt.data + 1)) == 0x25))) {
      fmt$StringBuilder$append$5(&builder, 0x25);
      (fmt.data += 2);
      continue;
    }
    if ((((*fmt.data) == 0x25) && (value_index >= fields.length))) {
      panic((str) { .data = "too few data arguments provided to 'format'", .length = 43 });
    }
    if ((((*fmt.data) == 0x25) && (value_index < fields.length))) {
      Field field  = (*(List$37$subscript(&fields, value_index)));
      any value  = (any){
        .type = (Type*)field.type,
        .ptr = (void*)Field$get$1451(&field, (&tuple))};
      fmt$format_any(value, (&builder), options);
      value_index++;
    }
    else{
      fmt$StringBuilder$append$5(&builder, (u32)(*fmt.data));
    }
    fmt.data++;
  }
  String $defer$return$value = fmt$StringBuilder$get_string(&builder);
  fmt$StringBuilder$deinit(&builder);
  return $defer$return$value;
  fmt$StringBuilder$deinit(&builder);
}
String elexify$SourceLocation$to_string(elexify$SourceLocation self) {
  List$19* files  = elexify$SourceLocation$files();
  String filename  = (*(List$19$subscript(&(*files), self.file)));
  return fmt$format$1451((str) { .data = "%:%:%", .length = 5 }, ($tuple19$4$4) {.$0 = filename, .$1 = self.line, .$2 = self.column}, fmt$FormatOptions$$default());
}
void elexify$SourceLocation$format(elexify$SourceLocation* self, fmt$StringBuilder* builder, fmt$FormatOptions options) {
  fmt$StringBuilder$append_then_free$19(builder, elexify$SourceLocation$to_string(*self));
}
String fmt$format$685(str fmt, $tuple18 tuple, fmt$FormatOptions options);
void fmt$StringBuilder$appendf$685(fmt$StringBuilder* self, str fmt, $tuple18 values, fmt$FormatOptions options) {
  String formatted  = fmt$format$685(fmt, values, options);
  fmt$StringBuilder$append$19(self, formatted);
  String$deinit(&formatted);
}
Result$19_18 fs$File$read_all$19(String filename_path);
f64 math$clamp(f64 v, f64 min, f64 max) {
  if ((v < min)) {
    return min;
  }
  if ((v > max)) {
    return max;
  }
  return v;
}
s32 math$max$1(s32 a, s32 b) {
  if ((a > b)) {
    return a;
  }
  return b;
}
s32 math$max$1(s32 a, s32 b);
typedef struct Slice$19 {
  String* data;
  u64 length;
} Slice$19;
extern s32  memcmp(void*, void*, u64);
String String$substr(String self, u64 start, u64 length) {
  if ((start >= self.length)) {
    return (String){0};
  }
  if (((start + length) > self.length)) {
    (length = (self.length - start));
  }
  return (String){
    .data = (u8*)Dyn_Allocator$copy(self.allocator, (self.data + start), sizeof(u8), length),
    .capacity = (u64)length,
    .length = (u64)length};
}
List$19 String$split$5(String self, u32 delimiter) {
  Slice$7 slice  = u32$as_byte_slice(delimiter);
  List$19 result = {};
  u64 start = {0};
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = self.length};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 i = $next.Some.$0;
      {
        if ((((i + slice.length) <= self.length) && (memcmp((self.data + i), slice.data, slice.length) == 0))) {
          List$19$push(&result, String$substr(self, start, (i - start)));
          (start = (i + slice.length));
          (i += (slice.length - 1));
        }
      }
    }
  }
  List$19$push(&result, String$substr(self, start, (self.length - start)));
  return result;
}
Slice$19 List$19$as_slice(List$19 self, RangeBase$1 range) {
  return (Slice$19){
    .data = (String*)(self.data + range.begin),
    .length = (u64)(range.end - range.begin)};
}
typedef struct Slice$19 Slice$19;
Iter$19 Slice$19$iter(Slice$19* self) {
  return (Iter$19){
    .ptr = (String*)(String*)self->data,
    .end = (String*)(self->data + self->length)};
}
String* Slice$19$subscript(Slice$19* self, u64 idx) {
  return (&self->data[idx]);
}
void fmt$StringBuilder$appendf$685(fmt$StringBuilder* self, str fmt, $tuple18 values, fmt$FormatOptions options);
str String$as_str(String self) {
  return (str){
    .data = (u8*)self.data,
    .length = (u64)self.length};
}
void elexify$lex_error$18(str msg, elexify$SourceLocation location) {
  fmt$StringBuilder builder = {};
  fmt$StringBuilder$append$18(&builder, (str) { .data = "\n\033[1;31mat:\n\t\033[1;34m", .length = 20 });
  elexify$SourceLocation$format(&location, (&builder), fmt$FormatOptions$$default());
  fmt$StringBuilder$append$18(&builder, (str) { .data = "\033[0m\n", .length = 5 });
  fmt$StringBuilder$appendf$685(&builder, (str) { .data = "\033[1;3;31merror: %", .length = 17 }, ($tuple18) {.$0 = msg}, fmt$FormatOptions$$default());
  fmt$StringBuilder$append$18(&builder, (str) { .data = "\033[0m\n", .length = 5 });
  String filename  = (*(List$19$subscript(&(*elexify$SourceLocation$files()), location.file)));
  String file_data  = Result$19_18$unwrap(fs$File$read_all$19(filename));
  s32 line  = (s32)location.line;
  s32 clamped_begin  = (s32)math$clamp((line - 3), (line - 3), line);
  s32 clamped_end  = (s32)math$clamp((line + 3), line, (line + 3));
  (clamped_begin = math$max$1(0, clamped_begin));
  (clamped_end = math$max$1(0, clamped_end));
  Slice$19 lines  = List$19$as_slice(String$split$5(file_data, 0xa), (RangeBase$1) {.begin = clamped_begin, .end = clamped_end});
  fmt$StringBuilder$append$18(&builder, (str) { .data = "\033[1;3;37m\n", .length = 10 });
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = lines.length};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 i = $next.Some.$0;
      {
        str line  = (str){
          .data = (u8*)(u8*)(*(Slice$19$subscript(&lines, i))).data,
          .length = (u64)(*(Slice$19$subscript(&lines, i))).length};
        fmt$StringBuilder$appendf$685(&builder, (str) { .data = "%\n", .length = 2 }, ($tuple18) {.$0 = line}, fmt$FormatOptions$$default());
        if ((i == 2)) {
          {
            RangeBase$1 $iterable = (RangeBase$1) {.begin = 1, .end = (location.column - 1)};
            RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
            while (1) {
              auto $next = RangeIter$1$next(&$iterator);
              if (!$next.index != 1) break;
              s32 i = $next.Some.$0;
              {
                fmt$StringBuilder$append$18(&builder, (str) { .data = " ", .length = 1 });
              }
            }
          }
          {
            RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = 3};
            RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
            while (1) {
              auto $next = RangeIter$1$next(&$iterator);
              if (!$next.index != 1) break;
              s32 i = $next.Some.$0;
              {
                fmt$StringBuilder$append$18(&builder, (str) { .data = "^", .length = 1 });
              }
            }
          }
          fmt$StringBuilder$append$18(&builder, (str) { .data = "\n", .length = 1 });
        }
      }
    }
  }
  String string  = fmt$StringBuilder$get_string(&builder);
  panic(String$as_str(string));
{
    fmt$StringBuilder$deinit(&builder);
    String$deinit(&file_data);
    {
      Slice$19 $iterable = lines;
      Iter$19 $iterator = Slice$19$iter(&$iterable);
      while (1) {
        auto $next = Iter$19$next(&$iterator);
        if (!$next.index != 1) break;
        String line = $next.Some.$0;
        {
          String$deinit(&line);
        }
      }
    }
  }
  fmt$StringBuilder$deinit(&builder);
  String$deinit(&string);
}
typedef struct $tuple7 $tuple7;
u8* Field$get$371(Field* self, $tuple7* source) {
  return ((u8*)source + self->offset);
}
String fmt$format$371(str fmt, $tuple7 tuple, fmt$FormatOptions options) {
  if ((fmt.length == 0)) {
    String $defer$return$value = (String){0};
    return $defer$return$value;
  }
  fmt$StringBuilder builder = {};
  s32 value_index  = 0;
  List$37 fields  = _type_info.data[371]->fields;
  if (List$37$is_empty(fields)) {
    return String$from$18((str) { .data = "()", .length = 2 });
  }
  while ((*fmt.data)) {
    if ((((*fmt.data) == 0x5c) && ((*(fmt.data + 1)) == 0x25))) {
      fmt$StringBuilder$append$5(&builder, 0x25);
      (fmt.data += 2);
      continue;
    }
    if ((((*fmt.data) == 0x25) && (value_index >= fields.length))) {
      panic((str) { .data = "too few data arguments provided to 'format'", .length = 43 });
    }
    if ((((*fmt.data) == 0x25) && (value_index < fields.length))) {
      Field field  = (*(List$37$subscript(&fields, value_index)));
      any value  = (any){
        .type = (Type*)field.type,
        .ptr = (void*)Field$get$371(&field, (&tuple))};
      fmt$format_any(value, (&builder), options);
      value_index++;
    }
    else{
      fmt$StringBuilder$append$5(&builder, (u32)(*fmt.data));
    }
    fmt.data++;
  }
  String $defer$return$value = fmt$StringBuilder$get_string(&builder);
  fmt$StringBuilder$deinit(&builder);
  return $defer$return$value;
  fmt$StringBuilder$deinit(&builder);
}
typedef struct $tuple19 $tuple19;
u8* Field$get$1075(Field* self, $tuple19* source) {
  return ((u8*)source + self->offset);
}
String fmt$format$1075(str fmt, $tuple19 tuple, fmt$FormatOptions options) {
  if ((fmt.length == 0)) {
    String $defer$return$value = (String){0};
    return $defer$return$value;
  }
  fmt$StringBuilder builder = {};
  s32 value_index  = 0;
  List$37 fields  = _type_info.data[1075]->fields;
  if (List$37$is_empty(fields)) {
    return String$from$18((str) { .data = "()", .length = 2 });
  }
  while ((*fmt.data)) {
    if ((((*fmt.data) == 0x5c) && ((*(fmt.data + 1)) == 0x25))) {
      fmt$StringBuilder$append$5(&builder, 0x25);
      (fmt.data += 2);
      continue;
    }
    if ((((*fmt.data) == 0x25) && (value_index >= fields.length))) {
      panic((str) { .data = "too few data arguments provided to 'format'", .length = 43 });
    }
    if ((((*fmt.data) == 0x25) && (value_index < fields.length))) {
      Field field  = (*(List$37$subscript(&fields, value_index)));
      any value  = (any){
        .type = (Type*)field.type,
        .ptr = (void*)Field$get$1075(&field, (&tuple))};
      fmt$format_any(value, (&builder), options);
      value_index++;
    }
    else{
      fmt$StringBuilder$append$5(&builder, (u32)(*fmt.data));
    }
    fmt.data++;
  }
  String $defer$return$value = fmt$StringBuilder$get_string(&builder);
  fmt$StringBuilder$deinit(&builder);
  return $defer$return$value;
  fmt$StringBuilder$deinit(&builder);
}
void fmt$StringBuilder$appendf$1075(fmt$StringBuilder* self, str fmt, $tuple19 values, fmt$FormatOptions options) {
  String formatted  = fmt$format$1075(fmt, values, options);
  fmt$StringBuilder$append$19(self, formatted);
  String$deinit(&formatted);
}
List$19 String$split$5(String self, u32 delimiter);
void elexify$lex_error$19(String msg, elexify$SourceLocation location) {
  fmt$StringBuilder builder = {};
  fmt$StringBuilder$append$18(&builder, (str) { .data = "\n\033[1;31mat:\n\t\033[1;34m", .length = 20 });
  elexify$SourceLocation$format(&location, (&builder), fmt$FormatOptions$$default());
  fmt$StringBuilder$append$18(&builder, (str) { .data = "\033[0m\n", .length = 5 });
  fmt$StringBuilder$appendf$1075(&builder, (str) { .data = "\033[1;3;31merror: %", .length = 17 }, ($tuple19) {.$0 = msg}, fmt$FormatOptions$$default());
  fmt$StringBuilder$append$18(&builder, (str) { .data = "\033[0m\n", .length = 5 });
  String filename  = (*(List$19$subscript(&(*elexify$SourceLocation$files()), location.file)));
  String file_data  = Result$19_18$unwrap(fs$File$read_all$19(filename));
  s32 line  = (s32)location.line;
  s32 clamped_begin  = (s32)math$clamp((line - 3), (line - 3), line);
  s32 clamped_end  = (s32)math$clamp((line + 3), line, (line + 3));
  (clamped_begin = math$max$1(0, clamped_begin));
  (clamped_end = math$max$1(0, clamped_end));
  Slice$19 lines  = List$19$as_slice(String$split$5(file_data, 0xa), (RangeBase$1) {.begin = clamped_begin, .end = clamped_end});
  fmt$StringBuilder$append$18(&builder, (str) { .data = "\033[1;3;37m\n", .length = 10 });
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = lines.length};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 i = $next.Some.$0;
      {
        str line  = (str){
          .data = (u8*)(u8*)(*(Slice$19$subscript(&lines, i))).data,
          .length = (u64)(*(Slice$19$subscript(&lines, i))).length};
        fmt$StringBuilder$appendf$685(&builder, (str) { .data = "%\n", .length = 2 }, ($tuple18) {.$0 = line}, fmt$FormatOptions$$default());
        if ((i == 2)) {
          {
            RangeBase$1 $iterable = (RangeBase$1) {.begin = 1, .end = (location.column - 1)};
            RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
            while (1) {
              auto $next = RangeIter$1$next(&$iterator);
              if (!$next.index != 1) break;
              s32 i = $next.Some.$0;
              {
                fmt$StringBuilder$append$18(&builder, (str) { .data = " ", .length = 1 });
              }
            }
          }
          {
            RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = 3};
            RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
            while (1) {
              auto $next = RangeIter$1$next(&$iterator);
              if (!$next.index != 1) break;
              s32 i = $next.Some.$0;
              {
                fmt$StringBuilder$append$18(&builder, (str) { .data = "^", .length = 1 });
              }
            }
          }
          fmt$StringBuilder$append$18(&builder, (str) { .data = "\n", .length = 1 });
        }
      }
    }
  }
  String string  = fmt$StringBuilder$get_string(&builder);
  panic(String$as_str(string));
{
    fmt$StringBuilder$deinit(&builder);
    String$deinit(&file_data);
    {
      Slice$19 $iterable = lines;
      Iter$19 $iterator = Slice$19$iter(&$iterable);
      while (1) {
        auto $next = Iter$19$next(&$iterator);
        if (!$next.index != 1) break;
        String line = $next.Some.$0;
        {
          String$deinit(&line);
        }
      }
    }
  }
  fmt$StringBuilder$deinit(&builder);
  String$deinit(&string);
}
void elexify$lex_error$18(str msg, elexify$SourceLocation location);
typedef struct $tuple5 {
  u32 $0;
} $tuple5;
typedef struct $tuple5 $tuple5;
u8* Field$get$422(Field* self, $tuple5* source) {
  return ((u8*)source + self->offset);
}
String fmt$format$422(str fmt, $tuple5 tuple, fmt$FormatOptions options) {
  if ((fmt.length == 0)) {
    String $defer$return$value = (String){0};
    return $defer$return$value;
  }
  fmt$StringBuilder builder = {};
  s32 value_index  = 0;
  List$37 fields  = _type_info.data[422]->fields;
  if (List$37$is_empty(fields)) {
    return String$from$18((str) { .data = "()", .length = 2 });
  }
  while ((*fmt.data)) {
    if ((((*fmt.data) == 0x5c) && ((*(fmt.data + 1)) == 0x25))) {
      fmt$StringBuilder$append$5(&builder, 0x25);
      (fmt.data += 2);
      continue;
    }
    if ((((*fmt.data) == 0x25) && (value_index >= fields.length))) {
      panic((str) { .data = "too few data arguments provided to 'format'", .length = 43 });
    }
    if ((((*fmt.data) == 0x25) && (value_index < fields.length))) {
      Field field  = (*(List$37$subscript(&fields, value_index)));
      any value  = (any){
        .type = (Type*)field.type,
        .ptr = (void*)Field$get$422(&field, (&tuple))};
      fmt$format_any(value, (&builder), options);
      value_index++;
    }
    else{
      fmt$StringBuilder$append$5(&builder, (u32)(*fmt.data));
    }
    fmt.data++;
  }
  String $defer$return$value = fmt$StringBuilder$get_string(&builder);
  fmt$StringBuilder$deinit(&builder);
  return $defer$return$value;
  fmt$StringBuilder$deinit(&builder);
}
typedef struct interned$Interned$19 interned$Interned$19;
u64 String$hash(String self) {
  return str$hash(String$as_str(self));
}
typedef struct map$Map$4_446 map$Map$4_446;
typedef struct List$1173 List$1173;
typedef struct List$1174 {
  List$1173* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$1174;
typedef struct map$Map$4_446 {
  List$1174 buckets;
  u64 length;
} map$Map$4_446;
static map$Map$4_446* interned$Interned$19$table() {
  static map$Map$4_446 table = {};
  return (&table);
}
typedef struct $tuple446 {
  String* $0;
} $tuple446;
typedef struct Option$446 Option$446;
typedef $tuple446 Option$446$Some;
typedef struct Option$446 {
  int index;
  union {
    Option$446$Some Some;
  };
} Option$446;
Option$446 None$1387() {
  return  (Option$446) { .index = 1};
}
u64 HASH_INITIAL_VALUE  = 0xCBF29CE484222325;
u64 HASH_FACTOR  = 0x100000001B3;
u64 u64$hash(u64 self) {
  u64 hash  = HASH_INITIAL_VALUE;
  (hash ^= self);
  (hash *= HASH_FACTOR);
  return hash;
}
typedef struct $tuple4$446 $tuple4$446;
typedef struct Iter$1173 {
  $tuple4$446* ptr;
  $tuple4$446* end;
} Iter$1173;
typedef struct $tuple4$446 {
  u64 $0;
  String* $1;
} $tuple4$446;
typedef struct List$1173 {
  $tuple4$446* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$1173;
typedef struct List$1174 List$1174;
List$1173* List$1174$subscript(List$1174* self, u64 idx) {
  return (&self->data[idx]);
}
Iter$1173 List$1173$iter(List$1173* self) {
  return (Iter$1173){
    .ptr = ($tuple4$446*)self->data,
    .end = ($tuple4$446*)($tuple4$446*)(self->data + self->length)};
}
typedef struct $tuple1173 {
  $tuple4$446 $0;
} $tuple1173;
typedef struct Option$1173 Option$1173;
typedef $tuple1173 Option$1173$Some;
typedef struct Option$1173 {
  int index;
  union {
    Option$1173$Some Some;
  };
} Option$1173;
typedef struct Iter$1173 Iter$1173;
Option$1173 Iter$1173$next(Iter$1173* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$1173) { .index = 1};
  }
  Option$1173 value  = (Option$1173) {
.index = 0,
.Some = ($tuple1173) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
Option$446 Some$446(String* t) {
  return (Option$446) {
.index = 0,
.Some = ($tuple446) {.$0 = t}};
}
Option$446 map$Map$4_446$get(map$Map$4_446* self, u64 search_key) {
  if ((self->buckets.length == 0)) {
    return None$1387();
  }
  u64 idx  = (u64$hash(search_key) % self->buckets.length);
  {
    Iter$1173 $iterator = List$1173$iter(&(*(List$1174$subscript(&self->buckets, idx))));
    while (1) {
      auto $next = Iter$1173$next(&$iterator);
      if (!$next.index != 1) break;
      $tuple4$446 pair = $next.Some.$0;
      {
        if ((pair.$0 == search_key)) {
          return Some$446(pair.$1);
        }
      }
    }
  }
  return None$1387();
}
bool Option$446$is_some(Option$446 self) {
if (self.index == 0) {
{
    return true;
  }
}
  return false;
}
String* Option$446$unwrap(Option$446 self) {
    auto $switch_target$16 = self;
if ($switch_target$16.index == 0) {
String* v = ($switch_target$16.Some.$0);
{
    return v;
  }
}
else {
{
    panic((str) { .data = "unwrapped a 'none' option", .length = 25 });
  }
}
;
  String* $default = {};
  return $default;
}
String* new$19(String initial_value) {
  String* ptr  = malloc(sizeof(String));
  ((*ptr) = initial_value);
  return ptr;
}
void List$1174$resize(List$1174* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(List$1173), self->capacity));
}
void List$1174$initialize(List$1174* self, u64 num_to_fill) {
  List$1174$resize(self, num_to_fill);
  memset(self->data, 0, (sizeof(List$1173) * self->capacity));
  (self->length = num_to_fill);
}
typedef struct IterMut$1173 {
  $tuple4$446* ptr;
  $tuple4$446* end;
} IterMut$1173;
IterMut$1173 List$1173$iter_mut(List$1173* self) {
  return (IterMut$1173){
    .ptr = ($tuple4$446*)self->data,
    .end = ($tuple4$446*)(self->data + self->length)};
}
typedef struct $tuple1175 {
  $tuple4$446* $0;
} $tuple1175;
typedef struct Option$1175 Option$1175;
typedef $tuple1175 Option$1175$Some;
typedef struct Option$1175 {
  int index;
  union {
    Option$1175$Some Some;
  };
} Option$1175;
typedef struct IterMut$1173 IterMut$1173;
Option$1175 IterMut$1173$next(IterMut$1173* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$1175) { .index = 1};
  }
  Option$1175 value  = (Option$1175) {
.index = 0,
.Some = ($tuple1175) {.$0 = self->ptr}};
  self->ptr++;
  return value;
}
void List$1173$resize(List$1173* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof($tuple4$446), self->capacity));
}
void List$1173$push(List$1173* self, $tuple4$446 v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$1173$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
void map$Map$4_446$insert(map$Map$4_446* self, u64 key, String* value) {
  if ((self->buckets.length == 0)) {
    List$1174$initialize(&self->buckets, 16);
  }
  u64 idx  = (u64$hash(key) % self->buckets.length);
  {
    IterMut$1173 $iterator = List$1173$iter_mut(&(*(List$1174$subscript(&self->buckets, idx))));
    while (1) {
      auto $next = IterMut$1173$next(&$iterator);
      if (!$next.index != 1) break;
      $tuple4$446* pair = $next.Some.$0;
      {
        if ((pair->$0 == key)) {
          (pair->$1 = value);
          return;
        }
      }
    }
  }
  List$1173$push(&(*(List$1174$subscript(&self->buckets, idx))), ($tuple4$446) {.$0 = key, .$1 = value});
  (self->length += 1);
}
void interned$Interned$19$insert_or_set(interned$Interned$19* self, String value) {
  u64 hash  = String$hash(value);
  map$Map$4_446* table  = interned$Interned$19$table();
  Option$446 result  = map$Map$4_446$get(table, hash);
  if (Option$446$is_some(result)) {
    (self->data = Option$446$unwrap(result));
  }
  else{
    (self->data = new$19(value));
    map$Map$4_446$insert(table, hash, self->data);
  }
}
interned$Interned$19 interned$Interned$19$new(String value) {
  interned$Interned$19 self = {};
  interned$Interned$19$insert_or_set(&self, value);
  return self;
}
elexify$Token elexify$Token$new(elexify$SourceLocation location, Option$19 value, u32 type) {
if (value.index == 0) {
String string = (value.Some.$0);
{
    return (elexify$Token){
      .value = (Option$1171)(Option$1171) {
.index = 0,
.Some = ($tuple1171) {.$0 = interned$Interned$19$new(string)}},
      .type = (u32)type,
      .location = (elexify$SourceLocation)location};
  }
}
  else{
    return (elexify$Token){
      .value =  (Option$1171) { .index = 1},
      .type = (u32)type,
      .location = (elexify$SourceLocation)location};
  }
}
void fmt$StringBuilder$append_byte(fmt$StringBuilder* self, u8 ch) {
  if ((!self->root)) {
    (self->root = fmt$StringBuilderBlock$new());
    (self->current = self->root);
  }
  if ((self->current->length == fmt$STRING_BUILDER_BLOCK_MAX_LEN)) {
    (self->current->next = fmt$StringBuilderBlock$new());
    (self->current = self->current->next);
  }
  (self->current->data[self->current->length] = ch);
  (self->current->length += 1);
}
extern s32  isalpha(s32);
extern s32  isalnum(s32);
typedef struct Option$5 Option$5;
typedef $tuple5 Option$5$Some;
typedef struct Option$5 {
  int index;
  union {
    Option$5$Some Some;
  };
} Option$5;
Option$5 None$421() {
  return  (Option$5) { .index = 1};
}
Iter$1482 List$1482$iter(List$1482* self) {
  return (Iter$1482){
    .ptr = ($tuple18$5*)self->data,
    .end = ($tuple18$5*)($tuple18$5*)(self->data + self->length)};
}
Option$5 Some$5(u32 t) {
  return (Option$5) {
.index = 0,
.Some = ($tuple5) {.$0 = t}};
}
Option$5 map$Map$18_5$get(map$Map$18_5* self, str search_key) {
  if ((self->buckets.length == 0)) {
    return None$421();
  }
  u64 idx  = (str$hash(search_key) % self->buckets.length);
  {
    Iter$1482 $iterator = List$1482$iter(&(*(List$1483$subscript(&self->buckets, idx))));
    while (1) {
      auto $next = Iter$1482$next(&$iterator);
      if (!$next.index != 1) break;
      $tuple18$5 pair = $next.Some.$0;
      {
        if ((str$eq(pair.$0, search_key))) {
          return Some$5(pair.$1);
        }
      }
    }
  }
  return None$421();
}
bool Option$5$is_some(Option$5 self) {
if (self.index == 0) {
{
    return true;
  }
}
  return false;
}
bool map$Map$18_5$contains(map$Map$18_5* self, str key) {
  return Option$5$is_some(map$Map$18_5$get(self, key));
}
u32 Option$5$unwrap(Option$5 self) {
    auto $switch_target$17 = self;
if ($switch_target$17.index == 0) {
u32 v = ($switch_target$17.Some.$0);
{
    return v;
  }
}
else {
{
    panic((str) { .data = "unwrapped a 'none' option", .length = 25 });
  }
}
;
  u32 $default = {0};
  return $default;
}
bool $lambda$7 (str a, str b)
{
  return (str$eq(a, b));
}

bool List$18$contains(List$18 self, str seek, bool(*comparator)(str, str)) {
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = self.length};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 idx = $next.Some.$0;
      {
        if (comparator(self.data[idx], seek)) {
          return true;
        }
      }
    }
  }
  return false;
}
String String$clone(String self) {
  Dyn_Allocator* allocator  = self.allocator;
  if ((allocator == NULL)) {
    (allocator = get_default_allocator());
  }
  return (String){
    .data = (u8*)Dyn_Allocator$copy(allocator, self.data, sizeof(u8), self.length),
    .length = (u64)self.length,
    .capacity = (u64)self.capacity,
    .allocator = (Dyn_Allocator*)allocator};
}
void String$append$19(String* self, String other) {
  Slice$7 slice  = String$as_byte_slice(other);
  if ((self->capacity == 0)) {
    (self->capacity = (256 / 3));
  }
  if (((self->length + slice.length) >= self->capacity)) {
    String$resize(self, ((self->capacity * 3) + slice.length));
  }
  memcpy((self->data + self->length), slice.data, slice.length);
  (self->length += slice.length);
  (self->data[self->length] = 0x0);
}
extern s32  ispunct(s32);
bool String$is_empty(String self) {
  return (self.length == 0);
}
extern s32  isdigit(s32);
void String$append$19(String* self, String other);
void String$append_then_free$19(String* self, String other) {
  String$append$19(self, other);
  String$deinit(&other);
}
void String$append_then_free$19(String* self, String other);
void elexify$Lexer$get_token(elexify$Lexer* self, elexify$State* state) {
  fmt$StringBuilder token_builder = {};
  while ((state->pos < state->input.length)) {
    fmt$StringBuilder$clear(&token_builder);
    u8 c  = (*(String$subscript(&state->input, state->pos)));
    if ((c == 0xa)) {
      state->pos++;
      state->line++;
      (state->col = 1);
      continue;
    }
    if (((c == 0x20) || (c == 0x9))) {
      state->pos++;
      state->col++;
      continue;
    }
    if ((((c == 0x2f) && ((state->pos + 1) < state->input.length)) && ((*(String$subscript(&state->input, (state->pos + 1)))) == 0x2f))) {
      (state->pos += 2);
      (state->col += 2);
      while (((c != 0xa) && (state->pos < state->input.length))) {
        state->pos++;
        (c = (*(String$subscript(&state->input, state->pos))));
      }
      if ((state->pos < state->input.length)) {
        state->pos++;
        (state->col = 1);
        state->line++;
      }
      continue;
    }
    if ((((c == 0x2f) && ((state->pos + 1) < state->input.length)) && ((*(String$subscript(&state->input, (state->pos + 1)))) == 0x2a))) {
      (state->pos += 2);
      (state->col += 2);
      while (((((state->pos + 1) < state->input.length) && ((*(String$subscript(&state->input, state->pos))) != 0x2a)) || ((*(String$subscript(&state->input, (state->pos + 1)))) != 0x2f))) {
        if (((*(String$subscript(&state->input, state->pos))) == 0xa)) {
          state->line++;
          (state->col = 1);
        }
        else{
          state->col++;
        }
        state->pos++;
        (c = (*(String$subscript(&state->input, state->pos))));
      }
      if ((state->pos < state->input.length)) {
        (state->pos += 2);
        (state->col += 2);
      }
      continue;
    }
    elexify$SourceLocation location  = (elexify$SourceLocation){
      .line = (u64)state->line,
      .column = (u64)state->col,
      .file = (u64)state->file_idx};
    if ((c == 0x27)) {
      u64 start  = state->pos;
      state->pos++;
      state->col++;
      (c = (*(String$subscript(&state->input, state->pos))));
      u32 codepoint  = (u32)(-1);
      if ((c == 0x5c)) {
        state->pos++;
        state->col++;
        (c = (*(String$subscript(&state->input, state->pos))));
        state->pos++;
        state->col++;
        if ((c == 0x6e)) {
          (codepoint = 0xa);
        }
        else
        if ((c == 0x76)) {
          (codepoint = 0xb);
        }
        else
        if ((c == 0x62)) {
          (codepoint = 0x8);
        }
        else
        if ((c == 0x74)) {
          (codepoint = 0x9);
        }
        else
        if ((c == 0x66)) {
          (codepoint = 0xc);
        }
        else
        if ((c == 0x72)) {
          (codepoint = 0xd);
        }
        else
        if ((c == 0x27)) {
          (codepoint = 0x27);
        }
        else
        if ((c == 0x5c)) {
          (codepoint = 0x5c);
        }
        else
        if ((c == 0x22)) {
          (codepoint = 0x22);
        }
        else
        if ((c == 0x30)) {
          (codepoint = 0x0);
        }
        else
        if ((((c == 0x78) || (c == 0x75)) || (c == 0x55))) {
          u64 num_digits = {0};
          if ((c == 0x78)) {
            (num_digits = 2);
          }
          else
          if ((c == 0x75)) {
            (num_digits = 4);
          }
          else{
            (num_digits = 8);
          }
          state->pos++;
          state->col++;
          (codepoint = 0);
          {
            RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = num_digits};
            RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
            while (1) {
              auto $next = RangeIter$1$next(&$iterator);
              if (!$next.index != 1) break;
              s32 i = $next.Some.$0;
              {
                if (((state->pos >= state->input.length) || (!isxdigit((*(String$subscript(&state->input, state->pos))))))) {
                  elexify$lex_error$18((str) { .data = "invalid hexadecimal escape sequence", .length = 35 }, location);
                }
                u8 buffer[2] = {(*(String$subscript(&state->input, state->pos))), 0x0};
                u8 hex_value  = (*(String$subscript(&state->input, state->pos)));
                if (((hex_value >= 0x30) && (hex_value <= 0x39))) {
                  (hex_value -= 0x30);
                }
                else
                if (((hex_value >= 0x61) && (hex_value <= 0x66))) {
                  (hex_value -= (0x61 - 10));
                }
                else
                if (((hex_value >= 0x41) && (hex_value <= 0x46))) {
                  (hex_value -= (0x41 - 10));
                }
                (codepoint = ((codepoint << 4) | hex_value));
                state->pos++;
                state->col++;
              }
            }
          }
        }
        else
        if (((c >= 0x30) && (c <= 0x37))) {
          (codepoint = 0);
          s32 i  = 0;
          while ((((i < 3) && (c > 0x30)) && (c < 0x37))) {
            (codepoint = ((codepoint << 3) | (c - 0x30)));
            state->pos++;
            state->col++;
            (c = (*(String$subscript(&state->input, state->pos))));
            i++;
          }
        }
        else{
          elexify$lex_error$19(fmt$format$371((str) { .data = "invalid escape sequence %", .length = 25 }, ($tuple7) {.$0 = c}, fmt$FormatOptions$$default()), location);
        }
      }
      else
      if (((c & 0x80) == 0)) {
        (codepoint = c);
        state->pos++;
        state->col++;
      }
      else{
        s32 num_bytes  = 0;
        if (((c & 0xE0) == 0xC0)) {
          (num_bytes = 2);
        }
        else
        if (((c & 0xF0) == 0xE0)) {
          (num_bytes = 3);
        }
        else
        if (((c & 0xF8) == 0xF0)) {
          (num_bytes = 4);
        }
        else{
          elexify$lex_error$18((str) { .data = "invalid utf8 char", .length = 17 }, location);
        }
        {
          RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = num_bytes};
          RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
          while (1) {
            auto $next = RangeIter$1$next(&$iterator);
            if (!$next.index != 1) break;
            s32 i = $next.Some.$0;
            {
              if (((state->pos >= state->input.length) || ((i > 0) && (((*(String$subscript(&state->input, state->pos))) & 0xC0) != 0x80)))) {
                elexify$lex_error$18((str) { .data = "invalid UTF-8 continuation byte", .length = 31 }, location);
              }
              (codepoint = ((codepoint << 6) | ((*(String$subscript(&state->input, state->pos))) & 0x3F)));
              state->pos++;
              state->col++;
            }
          }
        }
      }
      (c = (*(String$subscript(&state->input, state->pos))));
      if ((c != 0x27)) {
        elexify$lex_error$19(fmt$format$422((str) { .data = "invalid char literal: too many characters %", .length = 43 }, ($tuple5) {.$0 = codepoint}, fmt$FormatOptions$$default()), location);
      }
      state->pos++;
      state->col++;
      u8 buffer[32] = {0};
      snprintf(buffer, (32 * sizeof(u8)), "0x%X", codepoint);
      List$58$push(&self->lookahead_buffer, elexify$Token$new(location, Some$19(String$from_ptr(buffer)), elexify$TOKEN_CHAR));
      return;
    }
    if ((c == 0x22)) {
      state->pos++;
      state->col++;
      (c = (*(String$subscript(&state->input, state->pos))));
      while ((state->pos < state->input.length)) {
        (c = (*(String$subscript(&state->input, state->pos))));
        if ((c == 0x22)) {
          break;
        }
        if ((c == 0xa)) {
          elexify$lex_error$18((str) { .data = "You can't directly embed a '\\n' in string by just letting it span multiple lines", .length = 80 }, location);
        }
        else
        if ((c == 0x5c)) {
          if (((state->pos + 1) < state->input.length)) {
            fmt$StringBuilder$append_byte(&token_builder, c);
            state->pos++;
            state->col++;
            fmt$StringBuilder$append_byte(&token_builder, (*(String$subscript(&state->input, state->pos))));
            state->pos++;
            state->col++;
          }
          else{
            elexify$lex_error$18((str) { .data = "incomplete escape sequence at end of input", .length = 42 }, location);
          }
        }
        else{
          fmt$StringBuilder$append_byte(&token_builder, c);
          state->pos++;
          state->col++;
          (c = (*(String$subscript(&state->input, state->pos))));
        }
      }
      if ((c != 0x22)) {
        panic((str) { .data = "unescaped string", .length = 16 });
      }
      state->pos++;
      state->col++;
      List$58$push(&self->lookahead_buffer, elexify$Token$new(location, Some$19(fmt$StringBuilder$get_string(&token_builder)), elexify$TOKEN_STRING));
      return;
    }
    if (((isalpha(c) || (c == 0x5f)) || ((c & 0x80) != 0))) {
      while ((state->pos < state->input.length)) {
        if ((isalnum(c) || (c == 0x5f))) {
          fmt$StringBuilder$append_byte(&token_builder, c);
          state->pos++;
          state->col++;
          (c = (*(String$subscript(&state->input, state->pos))));
        }
        else
        if (((c & 0x80) != 0)) {
          s32 num_bytes  = 0;
          if (((c & 0xE0) == 0xC0)) {
            (num_bytes = 2);
          }
          else
          if (((c & 0xF0) == 0xE0)) {
            (num_bytes = 3);
          }
          else
          if (((c & 0xF8) == 0xF0)) {
            (num_bytes = 4);
          }
          else{
            break;
          }
          {
            RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = num_bytes};
            RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
            while (1) {
              auto $next = RangeIter$1$next(&$iterator);
              if (!$next.index != 1) break;
              s32 i = $next.Some.$0;
              {
                if (((state->pos >= state->input.length) || ((i > 0) && (((*(String$subscript(&state->input, state->pos))) & 0xC0) != 0x80)))) {
                  break;
                }
                fmt$StringBuilder$append_byte(&token_builder, (*(String$subscript(&state->input, state->pos))));
                state->pos++;
                state->col++;
              }
            }
          }
          (c = (*(String$subscript(&state->input, state->pos))));
        }
        else{
          break;
        }
      }
      String value  = fmt$StringBuilder$get_string(&token_builder);
      if (map$Map$18_5$contains(&self->keywords, String$as_str(value))) {
        List$58$push(&self->lookahead_buffer, elexify$Token$new(location, None$1074(), Option$5$unwrap(map$Map$18_5$get(&self->keywords, String$as_str(value)))));
        String$deinit(&value);
        return;
      }
      else
      if (List$18$contains(self->reserved, String$as_str(value), $lambda$7)) {
        String new_value  = String$clone(self->reserved_placeholder);
        String$append$19(&new_value, value);
        String$deinit(&value);
        (value = new_value);
      }
      List$58$push(&self->lookahead_buffer, elexify$Token$new(location, Some$19(value), elexify$TOKEN_IDENTIFIER));
      return;
    }
    if (ispunct(c)) {
      String longest_match  = (String){0};
      String current_match  = (String){0};
      while (((state->pos < state->input.length) && ispunct(c))) {
        if ((c == 0x22)) {
          break;
        }
        String$push(&current_match, (*(String$subscript(&state->input, state->pos))));
        Option$5 option  = map$Map$18_5$get(&self->operators, String$as_str(current_match));
        if (Option$5$is_some(option)) {
          (longest_match = current_match);
        }
        else
        if ((!String$is_empty(longest_match))) {
          List$58$push(&self->lookahead_buffer, elexify$Token$new(location, None$1074(), Option$5$unwrap(map$Map$18_5$get(&self->operators, String$as_str(longest_match)))));
          return;
        }
        state->pos++;
        state->col++;
        (c = (*(String$subscript(&state->input, state->pos))));
      }
      if ((!String$is_empty(longest_match))) {
        List$58$push(&self->lookahead_buffer, elexify$Token$new(location, None$1074(), Option$5$unwrap(map$Map$18_5$get(&self->operators, String$as_str(longest_match)))));
        return;
      }
      else{
        elexify$lex_error$19(fmt$format$1075((str) { .data = "unable to lex operator :: \'%\'", .length = 31 }, ($tuple19) {.$0 = current_match}, fmt$FormatOptions$$default()), location);
      }
    }
    if (isdigit(c)) {
      bool is_float  = false;
      bool is_hex  = false;
      bool is_bin  = false;
      if (((c == 0x30) && (((*(String$subscript(&state->input, (state->pos + 1)))) == 0x78) || ((*(String$subscript(&state->input, (state->pos + 1)))) == 0x58)))) {
        (is_hex = true);
        (state->pos += 2);
        (state->col += 2);
        (c = (*(String$subscript(&state->input, state->pos))));
      }
      else
      if (((c == 0x30) && (((*(String$subscript(&state->input, (state->pos + 1)))) == 0x62) || ((*(String$subscript(&state->input, (state->pos + 1)))) == 0x42)))) {
        (is_bin = true);
        (state->pos += 2);
        (state->col += 2);
        (c = (*(String$subscript(&state->input, state->pos))));
      }
      while (((state->pos < state->input.length) && ((((isdigit(c) || (c == 0x2e)) || (is_hex && isxdigit(c))) || (is_bin && ((c == 0x30) || (c == 0x31)))) || (c == 0x5f)))) {
        if ((c == 0x5f)) {
          state->pos++;
          state->col++;
          (c = (*(String$subscript(&state->input, state->pos))));
        }
        if ((((c == 0x2e) && ((state->pos + 1) < state->input.length)) && (((*(String$subscript(&state->input, (state->pos + 1)))) == 0x2e) || (!isdigit((*(String$subscript(&state->input, (state->pos + 1))))))))) {
          break;
        }
        if ((c == 0x2e)) {
          if (is_float) {
            elexify$lex_error$18((str) { .data = "got too many '.' periods in a float literal.", .length = 44 }, location);
          }
          (is_float = true);
        }
        fmt$StringBuilder$append_byte(&token_builder, c);
        state->pos++;
        state->col++;
        (c = (*(String$subscript(&state->input, state->pos))));
        if ((c == 0x5f)) {
          state->pos++;
          state->col++;
          (c = (*(String$subscript(&state->input, state->pos))));
        }
      }
      String value  = fmt$StringBuilder$get_string(&token_builder);
      if (is_hex) {
        String hex  = String$from$18((str) { .data = "0x", .length = 2 });
        String$append_then_free$19(&hex, value);
        List$58$push(&self->lookahead_buffer, elexify$Token$new(location, Some$19(hex), elexify$TOKEN_INTEGER));
      }
      else
      if (is_bin) {
        String bin  = String$from$18((str) { .data = "0b", .length = 2 });
        String$append_then_free$19(&bin, value);
        List$58$push(&self->lookahead_buffer, elexify$Token$new(location, Some$19(bin), elexify$TOKEN_INTEGER));
      }
      else
      if ((!is_float)) {
        List$58$push(&self->lookahead_buffer, elexify$Token$new(location, Some$19(value), elexify$TOKEN_INTEGER));
      }
      else{
        List$58$push(&self->lookahead_buffer, elexify$Token$new(location, Some$19(value), elexify$TOKEN_FLOAT));
      }
      return;
    }
  }
  List$58$push(&self->lookahead_buffer, elexify$Token$Eof());
  fmt$StringBuilder$deinit(&token_builder);
}
typedef struct $tuple58 {
  elexify$Token $0;
} $tuple58;
typedef struct Option$58 Option$58;
typedef $tuple58 Option$58$Some;
typedef struct Option$58 {
  int index;
  union {
    Option$58$Some Some;
  };
} Option$58;
Option$58 Some$58(elexify$Token t) {
  return (Option$58) {
.index = 0,
.Some = ($tuple58) {.$0 = t}};
}
Option$58 None$1913() {
  return  (Option$58) { .index = 1};
}
Option$58 List$58$back(List$58 self) {
  if ((self.length > 0)) {
    return Some$58(self.data[(self.length - 1)]);
  }
  return None$1913();
}
elexify$Token Option$58$unwrap(Option$58 self) {
    auto $switch_target$18 = self;
if ($switch_target$18.index == 0) {
elexify$Token v = ($switch_target$18.Some.$0);
{
    return v;
  }
}
else {
{
    panic((str) { .data = "unwrapped a 'none' option", .length = 25 });
  }
}
;
  elexify$Token $default = {};
  return $default;
}
elexify$State List$59$pop(List$59* self) {
  elexify$State value  = self->data[(self->length - 1)];
  (self->length -= 1);
  return value;
}
void elexify$Lexer$fill_buffer_if_needed(elexify$Lexer* self) {
  while ((self->lookahead_buffer.length < 8)) {
    if (List$59$is_empty(self->states)) {
      List$58$push(&self->lookahead_buffer, elexify$Token$Eof());
    }
    else{
      elexify$Lexer$get_token(self, Option$1794$unwrap(List$59$back_mut(&self->states)));
      elexify$Token token  = Option$58$unwrap(List$58$back(self->lookahead_buffer));
      if ((token.type == elexify$TOKEN_EOF)) {
        List$59$pop(&self->states);
      }
    }
  }
}
Option$58 List$58$front(List$58 self) {
  if ((self.length > 0)) {
    return Some$58(self.data[0]);
  }
  return None$1913();
}
elexify$Token elexify$Lexer$peek(elexify$Lexer* self) {
  elexify$Lexer$fill_buffer_if_needed(self);
  return Option$58$unwrap(List$58$front(self->lookahead_buffer));
}
bool elexify$Token$is_eof(elexify$Token self) {
  return (self.type == elexify$TOKEN_EOF);
}
typedef struct List$1171 {
  interned$Interned$19* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$1171;
typedef struct parser$Statement parser$Statement;
typedef struct List$3382 {
  parser$Statement** data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$3382;
typedef struct parser$Block {
  List$3382 statements;
  parser$Scope scope;
} parser$Block;
typedef struct parser$Function {
  List$1171 parameters;
  parser$Block block;
} parser$Function;
extern s32  memmove(void*, void*, s64);
elexify$Token List$58$pop_front(List$58* self) {
  elexify$Token value  = self->data[0];
  memmove(self->data, (self->data + 1), (sizeof(elexify$Token) * (self->length - 1)));
  (self->length -= 1);
  return value;
}
elexify$Token elexify$Lexer$eat(elexify$Lexer* self) {
  elexify$Lexer$fill_buffer_if_needed(self);
  return List$58$pop_front(&self->lookahead_buffer);
}
typedef struct $tuple5$5 {
  u32 $0;
  u32 $1;
} $tuple5$5;
typedef struct $tuple5$5 $tuple5$5;
u8* Field$get$2033(Field* self, $tuple5$5* source) {
  return ((u8*)source + self->offset);
}
String fmt$format$2033(str fmt, $tuple5$5 tuple, fmt$FormatOptions options) {
  if ((fmt.length == 0)) {
    String $defer$return$value = (String){0};
    return $defer$return$value;
  }
  fmt$StringBuilder builder = {};
  s32 value_index  = 0;
  List$37 fields  = _type_info.data[2033]->fields;
  if (List$37$is_empty(fields)) {
    return String$from$18((str) { .data = "()", .length = 2 });
  }
  while ((*fmt.data)) {
    if ((((*fmt.data) == 0x5c) && ((*(fmt.data + 1)) == 0x25))) {
      fmt$StringBuilder$append$5(&builder, 0x25);
      (fmt.data += 2);
      continue;
    }
    if ((((*fmt.data) == 0x25) && (value_index >= fields.length))) {
      panic((str) { .data = "too few data arguments provided to 'format'", .length = 43 });
    }
    if ((((*fmt.data) == 0x25) && (value_index < fields.length))) {
      Field field  = (*(List$37$subscript(&fields, value_index)));
      any value  = (any){
        .type = (Type*)field.type,
        .ptr = (void*)Field$get$2033(&field, (&tuple))};
      fmt$format_any(value, (&builder), options);
      value_index++;
    }
    else{
      fmt$StringBuilder$append$5(&builder, (u32)(*fmt.data));
    }
    fmt.data++;
  }
  String $defer$return$value = fmt$StringBuilder$get_string(&builder);
  fmt$StringBuilder$deinit(&builder);
  return $defer$return$value;
  fmt$StringBuilder$deinit(&builder);
}
elexify$Token elexify$Lexer$expect(elexify$Lexer* self, u32 type) {
  elexify$Token token  = elexify$Lexer$eat(self);
  if ((token.type != type)) {
    elexify$lex_error$19(fmt$format$2033((str) { .data = "unexpected token: '%' ...\nexpected '%' instead.", .length = 47 }, ($tuple5$5) {.$0 = token.type, .$1 = type}, fmt$FormatOptions$$default()), token.location);
  }
  return token;
}
bool elexify$Token$is_type(elexify$Token self, u32 type) {
  return (self.type == type);
}
interned$Interned$19 Option$1171$unwrap(Option$1171 self) {
    auto $switch_target$19 = self;
if ($switch_target$19.index == 0) {
interned$Interned$19 v = ($switch_target$19.Some.$0);
{
    return v;
  }
}
else {
{
    panic((str) { .data = "unwrapped a 'none' option", .length = 25 });
  }
}
;
  interned$Interned$19 $default = {};
  return $default;
}
typedef struct List$1171 List$1171;
void List$1171$resize(List$1171* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(interned$Interned$19), self->capacity));
}
void List$1171$push(List$1171* self, interned$Interned$19 v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$1171$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
typedef struct parser$Expression parser$Expression;
typedef enum {
  parser$Precedence$Assignment = 0,
  parser$Precedence$Additive = 1,
  parser$Precedence$Multiplicative = 2
} parser$Precedence;
parser$Expression* parser$parse_expression(elexify$Lexer* lexer);
extern s32  atoi(u8*);
typedef struct $tuple0 {
  s64 $0;
} $tuple0;
typedef struct $tuple3489$2051 {
  parser$Expression* $0;
  lexer$TType $1;
} $tuple3489$2051;
typedef struct $tuple3489$3489$2051 {
  parser$Expression* $0;
  parser$Expression* $1;
  lexer$TType $2;
} $tuple3489$3489$2051;
typedef struct List$3489 {
  parser$Expression** data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$3489;
typedef struct $tuple1171$3495 {
  interned$Interned$19 $0;
  List$3489 $1;
} $tuple1171$3495;
typedef struct parser$Expression parser$Expression;
typedef $tuple0 parser$Expression$Literal;
typedef $tuple1171 parser$Expression$Identifier;
typedef $tuple3489$2051 parser$Expression$Unary;
typedef $tuple3489$3489$2051 parser$Expression$Binary;
typedef $tuple1171$3495 parser$Expression$Call;
typedef struct parser$Expression {
  int index;
  union {
    parser$Expression$Literal Literal;
    parser$Expression$Identifier Identifier;
    parser$Expression$Unary Unary;
    parser$Expression$Binary Binary;
    parser$Expression$Call Call;
  };
} parser$Expression;
parser$Expression* new$143(parser$Expression initial_value) {
  parser$Expression* ptr  = malloc(sizeof(parser$Expression));
  ((*ptr) = initial_value);
  return ptr;
}
parser$Expression* new$143(parser$Expression initial_value);
parser$Expression* parser$parse_primary(elexify$Lexer* lexer) {
  elexify$Token token  = elexify$Lexer$eat(lexer);
    auto $switch_target$20 = token.type;
  if ($switch_target$20 == lexer$TType$OpenParen) {
    parser$Expression* expr  = parser$parse_expression(lexer);
    elexify$Lexer$expect(lexer, lexer$TType$CloseParen);
    return expr;
  }
  else   if ($switch_target$20 == lexer$TType$Integer) {
    String string  = (*Option$1171$unwrap(token.value).data);
    s32 integer  = atoi(string.data);
    String$deinit(&string);
    return new$143((parser$Expression) {
.index = 0,
.Literal = ($tuple0) {.$0 = integer}});
  }
  else   if ($switch_target$20 == lexer$TType$Identifier) {
    interned$Interned$19 string  = Option$1171$unwrap(token.value);
    return new$143((parser$Expression) {
.index = 1,
.Identifier = ($tuple1171) {.$0 = string}});
  }
  else   if ($switch_target$20 == lexer$TType$Char) {
    String string  = (*Option$1171$unwrap(token.value).data);
    s32 integer  = atoi(string.data);
    String$deinit(&string);
    return new$143((parser$Expression) {
.index = 0,
.Literal = ($tuple0) {.$0 = integer}});
  }
;
  elexify$lex_error$18((str) { .data = "failed to parse primary expression", .length = 34 }, token.location);
  return NULL;
}
typedef struct List$3489 List$3489;
void List$3489$resize(List$3489* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(parser$Expression*), self->capacity));
}
void List$3489$push(List$3489* self, parser$Expression* v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$3489$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
parser$Expression* parser$parse_postfix(elexify$Lexer* lexer) {
  parser$Expression* left  = parser$parse_primary(lexer);
    auto $switch_target$21 = elexify$Lexer$peek(lexer).type;
  if ($switch_target$21 == lexer$TType$OpenParen) {
if (left->index == 1) {
interned$Interned$19 identifier = (left->Identifier.$0);
{
      interned$Interned$19 callee  = identifier;
      elexify$Lexer$eat(lexer);
      List$3489 arguments = {};
      while ((!elexify$Token$is_type(elexify$Lexer$peek(lexer), lexer$TType$CloseParen))) {
        List$3489$push(&arguments, parser$parse_expression(lexer));
        if ((!elexify$Token$is_type(elexify$Lexer$peek(lexer), lexer$TType$CloseParen))) {
          elexify$Lexer$expect(lexer, lexer$TType$Comma);
        }
      }
      elexify$Lexer$expect(lexer, lexer$TType$CloseParen);
      return new$143((parser$Expression) {
.index = 4,
.Call = ($tuple1171$3495) {.$0 = callee, .$1 = arguments}});
    }
}
    else{
      elexify$lex_error$18((str) { .data = "can only call an identifier right now", .length = 37 }, elexify$Lexer$peek(lexer).location);
      return NULL;
    }
  }
;
  return left;
}
parser$Expression* parser$parse_unary(elexify$Lexer* lexer) {
  parser$Expression* left  = parser$parse_postfix(lexer);
  elexify$Token token  = elexify$Lexer$peek(lexer);
    auto $switch_target$22 = token.type;
  if ($switch_target$22 == lexer$TType$Sub) {
    elexify$Lexer$eat(lexer);
    return new$143((parser$Expression) {
.index = 2,
.Unary = ($tuple3489$2051) {.$0 = left, .$1 = token.type}});
  }
;
  return left;
}
u32 u32$max_value() {
  return 4294967295;
}
s32 u32$to_precedence(u32 self) {
    auto $switch_target$23 = self;
  if ($switch_target$23 == lexer$TType$Add) {
    return parser$Precedence$Additive;
  }
  else   if ($switch_target$23 == lexer$TType$Sub) {
    return parser$Precedence$Additive;
  }
  else   if ($switch_target$23 == lexer$TType$Mul) {
    return parser$Precedence$Multiplicative;
  }
  else   if ($switch_target$23 == lexer$TType$Div) {
    return parser$Precedence$Multiplicative;
  }
  else   if ($switch_target$23 == lexer$TType$Modulo) {
    return parser$Precedence$Multiplicative;
  }
  else   if ($switch_target$23 == lexer$TType$Assign) {
    return parser$Precedence$Assignment;
  }
;
  return u32$max_value();
}
parser$Expression* parser$parse_binary(elexify$Lexer* lexer, s32 min_precedence);
parser$Expression* parser$parse_binary(elexify$Lexer* lexer, s32 min_precedence) {
  parser$Expression* left  = parser$parse_unary(lexer);
  while (true) {
    elexify$Token token  = elexify$Lexer$peek(lexer);
    s32 precedence  = u32$to_precedence(token.type);
    if ((precedence < min_precedence)) {
      break;
    }
    elexify$Lexer$eat(lexer);
    parser$Expression* right  = parser$parse_binary(lexer, (precedence + 1));
    (left = new$143((parser$Expression) {
.index = 3,
.Binary = ($tuple3489$3489$2051) {.$0 = left, .$1 = right, .$2 = token.type}}));
  }
  return left;
}
parser$Expression* parser$parse_expression(elexify$Lexer* lexer) {
  return parser$parse_binary(lexer, 0);
}
typedef struct $tuple3489 {
  parser$Expression* $0;
} $tuple3489;
typedef struct $tuple3489$141 {
  parser$Expression* $0;
  parser$Block $1;
} $tuple3489$141;
typedef struct parser$Statement parser$Statement;
typedef $tuple1171 parser$Statement$Extrn;
typedef $tuple1171 parser$Statement$Auto;
typedef $tuple3489 parser$Statement$Expression;
typedef $tuple3489$141 parser$Statement$If;
typedef struct parser$Statement {
  int index;
  union {
    parser$Statement$Extrn Extrn;
    parser$Statement$Auto Auto;
    parser$Statement$Expression Expression;
    parser$Statement$If If;
  };
} parser$Statement;
parser$Statement* new$142(parser$Statement initial_value) {
  parser$Statement* ptr  = malloc(sizeof(parser$Statement));
  ((*ptr) = initial_value);
  return ptr;
}
parser$Block parser$parse_block(elexify$Lexer* lexer);
parser$Statement* parser$parse_statement(elexify$Lexer* lexer) {
  elexify$Token token  = elexify$Lexer$peek(lexer);
    auto $switch_target$24 = token.type;
  if ($switch_target$24 == lexer$TType$Identifier) {
    parser$Statement* expr  = new$142((parser$Statement) {
.index = 2,
.Expression = ($tuple3489) {.$0 = parser$parse_expression(lexer)}});
    elexify$Lexer$expect(lexer, lexer$TType$Semicolon);
    return expr;
  }
  else   if ($switch_target$24 == lexer$TType$Extrn) {
    elexify$Lexer$eat(lexer);
    interned$Interned$19 identifier  = Option$1171$unwrap(elexify$Lexer$expect(lexer, lexer$TType$Identifier).value);
    elexify$Lexer$expect(lexer, lexer$TType$Semicolon);
    return new$142((parser$Statement) {
.index = 0,
.Extrn = ($tuple1171) {.$0 = identifier}});
  }
  else   if ($switch_target$24 == lexer$TType$Auto) {
    elexify$Lexer$eat(lexer);
    interned$Interned$19 identifier  = Option$1171$unwrap(elexify$Lexer$expect(lexer, lexer$TType$Identifier).value);
    elexify$Lexer$expect(lexer, lexer$TType$Semicolon);
    return new$142((parser$Statement) {
.index = 1,
.Auto = ($tuple1171) {.$0 = identifier}});
  }
  else   if ($switch_target$24 == lexer$TType$If) {
    elexify$Lexer$eat(lexer);
    elexify$Lexer$expect(lexer, lexer$TType$OpenParen);
    parser$Expression* condition  = parser$parse_expression(lexer);
    elexify$Lexer$expect(lexer, lexer$TType$CloseParen);
    parser$Block block  = parser$parse_block(lexer);
    return new$142((parser$Statement) {
.index = 3,
.If = ($tuple3489$141) {.$0 = condition, .$1 = block}});
  }
;
  elexify$lex_error$18((str) { .data = "failed to parse statement", .length = 25 }, token.location);
  return NULL;
}
typedef struct List$3382 List$3382;
void List$3382$resize(List$3382* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(parser$Statement*), self->capacity));
}
void List$3382$push(List$3382* self, parser$Statement* v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$3382$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
parser$Block parser$parse_block(elexify$Lexer* lexer) {
  parser$Block block = {};
  if ((!elexify$Token$is_type(elexify$Lexer$peek(lexer), lexer$TType$OpenCurly))) {
    List$3382$push(&block.statements, parser$parse_statement(lexer));
    return block;
  }
  elexify$Lexer$expect(lexer, lexer$TType$OpenCurly);
  while ((!elexify$Token$is_type(elexify$Lexer$peek(lexer), lexer$TType$CloseCurly))) {
    List$3382$push(&block.statements, parser$parse_statement(lexer));
  }
  elexify$Lexer$expect(lexer, lexer$TType$CloseCurly);
  return block;
}
parser$Function parser$parse_function(elexify$Lexer* lexer) {
  elexify$Token name  = elexify$Lexer$expect(lexer, lexer$TType$Identifier);
  elexify$Lexer$expect(lexer, lexer$TType$OpenParen);
  parser$Function function = {};
  while (elexify$Token$is_type(elexify$Lexer$peek(lexer), lexer$TType$Identifier)) {
    List$1171$push(&function.parameters, Option$1171$unwrap(elexify$Lexer$eat(lexer).value));
    if ((!elexify$Token$is_type(elexify$Lexer$peek(lexer), lexer$TType$CloseParen))) {
      elexify$Lexer$expect(lexer, lexer$TType$Comma);
    }
  }
  elexify$Lexer$expect(lexer, lexer$TType$CloseParen);
  (function.block = parser$parse_block(lexer));
  return function;
}
typedef struct List$138 List$138;
void List$138$resize(List$138* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(parser$Function), self->capacity));
}
void List$138$push(List$138* self, parser$Function v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$138$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
parser$Program parser$parse_program(elexify$Lexer* lexer) {
  parser$Program program = {};
  while ((!elexify$Token$is_eof(elexify$Lexer$peek(lexer)))) {
    List$138$push(&program.functions, parser$parse_function(lexer));
  }
  return program;
}
typedef struct analyzer$Analyzer {
  parser$Scope* current_scope;
} analyzer$Analyzer;
typedef struct analyzer$Analyzer analyzer$Analyzer;
typedef struct Iter$138 {
  parser$Function* ptr;
  parser$Function* end;
} Iter$138;
Iter$138 List$138$iter(List$138* self) {
  return (Iter$138){
    .ptr = (parser$Function*)self->data,
    .end = (parser$Function*)(parser$Function*)(self->data + self->length)};
}
typedef struct $tuple138 {
  parser$Function $0;
} $tuple138;
typedef struct Option$138 Option$138;
typedef $tuple138 Option$138$Some;
typedef struct Option$138 {
  int index;
  union {
    Option$138$Some Some;
  };
} Option$138;
typedef struct Iter$138 Iter$138;
Option$138 Iter$138$next(Iter$138* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$138) { .index = 1};
  }
  Option$138 value  = (Option$138) {
.index = 0,
.Some = ($tuple138) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
typedef struct Iter$1171 {
  interned$Interned$19* ptr;
  interned$Interned$19* end;
} Iter$1171;
Iter$1171 List$1171$iter(List$1171* self) {
  return (Iter$1171){
    .ptr = (interned$Interned$19*)self->data,
    .end = (interned$Interned$19*)(interned$Interned$19*)(self->data + self->length)};
}
typedef struct Iter$1171 Iter$1171;
Option$1171 Iter$1171$next(Iter$1171* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$1171) { .index = 1};
  }
  Option$1171 value  = (Option$1171) {
.index = 0,
.Some = ($tuple1171) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
typedef enum {
  parser$BType$Integer = 0,
  parser$BType$Function = 1,
  parser$BType$Pointer = 2
} parser$BType;
typedef struct llvm$LLVMOpaqueValue llvm$LLVMOpaqueValue;
typedef struct List$2791 {
  s32 data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$2791;
typedef struct $tuple2792$2791 {
  List$2791 $0;
  parser$BType $1;
} $tuple2792$2791;
typedef struct $tuple2898 {
  $tuple2792$2791 $0;
} $tuple2898;
typedef struct Option$2898 Option$2898;
typedef $tuple2898 Option$2898$Some;
typedef struct Option$2898 {
  int index;
  union {
    Option$2898$Some Some;
  };
} Option$2898;
typedef struct parser$Variable {
  s32 type;
  llvm$LLVMOpaqueValue* llvm_value;
  Option$2898 inferred_function_signature;
} parser$Variable;
typedef struct $tuple137 {
  parser$Variable $0;
} $tuple137;
typedef struct Option$137 Option$137;
typedef $tuple137 Option$137$Some;
typedef struct Option$137 {
  int index;
  union {
    Option$137$Some Some;
  };
} Option$137;
Option$137 None$3230() {
  return  (Option$137) { .index = 1};
}
parser$Variable Option$137$or_else(Option$137 self, parser$Variable fallback) {
if (self.index == 0) {
parser$Variable v = (self.Some.$0);
{
    return v;
  }
}
  else{
    return fallback;
  }
}
typedef struct map$Map$1171_137 map$Map$1171_137;
typedef struct List$3017 List$3017;
typedef struct $tuple1171$137 $tuple1171$137;
typedef struct List$3016 {
  $tuple1171$137* data;
  u64 length;
  u64 capacity;
  Dyn_Allocator* allocator;
} List$3016;
void List$3017$resize(List$3017* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(List$3016), self->capacity));
}
void List$3017$initialize(List$3017* self, u64 num_to_fill) {
  List$3017$resize(self, num_to_fill);
  memset(self->data, 0, (sizeof(List$3016) * self->capacity));
  (self->length = num_to_fill);
}
u64 interned$Interned$19$hash(interned$Interned$19 self) {
  return String$hash(*self.data);
}
typedef struct IterMut$3016 {
  $tuple1171$137* ptr;
  $tuple1171$137* end;
} IterMut$3016;
typedef struct $tuple1171$137 {
  interned$Interned$19 $0;
  parser$Variable $1;
} $tuple1171$137;
List$3016* List$3017$subscript(List$3017* self, u64 idx) {
  return (&self->data[idx]);
}
IterMut$3016 List$3016$iter_mut(List$3016* self) {
  return (IterMut$3016){
    .ptr = ($tuple1171$137*)self->data,
    .end = ($tuple1171$137*)(self->data + self->length)};
}
typedef struct $tuple3018 {
  $tuple1171$137* $0;
} $tuple3018;
typedef struct Option$3018 Option$3018;
typedef $tuple3018 Option$3018$Some;
typedef struct Option$3018 {
  int index;
  union {
    Option$3018$Some Some;
  };
} Option$3018;
typedef struct IterMut$3016 IterMut$3016;
Option$3018 IterMut$3016$next(IterMut$3016* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$3018) { .index = 1};
  }
  Option$3018 value  = (Option$3018) {
.index = 0,
.Some = ($tuple3018) {.$0 = self->ptr}};
  self->ptr++;
  return value;
}
bool interned$Interned$19$eq(interned$Interned$19 self, interned$Interned$19 other) {
  return (self.data == other.data);
}
void List$3016$resize(List$3016* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof($tuple1171$137), self->capacity));
}
void List$3016$push(List$3016* self, $tuple1171$137 v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$3016$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
void map$Map$1171_137$insert(map$Map$1171_137* self, interned$Interned$19 key, parser$Variable value) {
  if ((self->buckets.length == 0)) {
    List$3017$initialize(&self->buckets, 16);
  }
  u64 idx  = (interned$Interned$19$hash(key) % self->buckets.length);
  {
    IterMut$3016 $iterator = List$3016$iter_mut(&(*(List$3017$subscript(&self->buckets, idx))));
    while (1) {
      auto $next = IterMut$3016$next(&$iterator);
      if (!$next.index != 1) break;
      $tuple1171$137* pair = $next.Some.$0;
      {
        if ((interned$Interned$19$eq(pair->$0, key))) {
          (pair->$1 = value);
          return;
        }
      }
    }
  }
  List$3016$push(&(*(List$3017$subscript(&self->buckets, idx))), ($tuple1171$137) {.$0 = key, .$1 = value});
  (self->length += 1);
}
void parser$Scope$insert(parser$Scope* self, interned$Interned$19 name, Option$137 variable) {
  map$Map$1171_137$insert(&self->variables, name, Option$137$or_else(variable, (parser$Variable){
    .type = (s32)parser$BType$Integer}));
}
Option$3003 Some$3003(parser$Scope* t) {
  return (Option$3003) {
.index = 0,
.Some = ($tuple3003) {.$0 = t}};
}
typedef struct Iter$3382 {
  parser$Statement** ptr;
  parser$Statement** end;
} Iter$3382;
Iter$3382 List$3382$iter(List$3382* self) {
  return (Iter$3382){
    .ptr = (parser$Statement**)self->data,
    .end = (parser$Statement**)(parser$Statement**)(self->data + self->length)};
}
typedef struct $tuple3382 {
  parser$Statement* $0;
} $tuple3382;
typedef struct Option$3382 Option$3382;
typedef $tuple3382 Option$3382$Some;
typedef struct Option$3382 {
  int index;
  union {
    Option$3382$Some Some;
  };
} Option$3382;
typedef struct Iter$3382 Iter$3382;
Option$3382 Iter$3382$next(Iter$3382* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$3382) { .index = 1};
  }
  Option$3382 value  = (Option$3382) {
.index = 0,
.Some = ($tuple3382) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
void analyzer$Analyzer$visit_extrn(analyzer$Analyzer* self, interned$Interned$19 identifier) {
}
void analyzer$Analyzer$visit_auto(analyzer$Analyzer* self, interned$Interned$19 identifier) {
}
typedef struct parser$Variable parser$Variable;
typedef struct $tuple3243 {
  parser$Variable* $0;
} $tuple3243;
typedef struct Option$3243 Option$3243;
typedef $tuple3243 Option$3243$Some;
typedef struct Option$3243 {
  int index;
  union {
    Option$3243$Some Some;
  };
} Option$3243;
typedef struct Iter$3016 {
  $tuple1171$137* ptr;
  $tuple1171$137* end;
} Iter$3016;
Iter$3016 List$3016$iter(List$3016* self) {
  return (Iter$3016){
    .ptr = ($tuple1171$137*)self->data,
    .end = ($tuple1171$137*)($tuple1171$137*)(self->data + self->length)};
}
typedef struct $tuple3016 {
  $tuple1171$137 $0;
} $tuple3016;
typedef struct Option$3016 Option$3016;
typedef $tuple3016 Option$3016$Some;
typedef struct Option$3016 {
  int index;
  union {
    Option$3016$Some Some;
  };
} Option$3016;
typedef struct Iter$3016 Iter$3016;
Option$3016 Iter$3016$next(Iter$3016* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$3016) { .index = 1};
  }
  Option$3016 value  = (Option$3016) {
.index = 0,
.Some = ($tuple3016) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
Option$137 Some$137(parser$Variable t) {
  return (Option$137) {
.index = 0,
.Some = ($tuple137) {.$0 = t}};
}
Option$137 map$Map$1171_137$get(map$Map$1171_137* self, interned$Interned$19 search_key) {
  if ((self->buckets.length == 0)) {
    return None$3230();
  }
  u64 idx  = (interned$Interned$19$hash(search_key) % self->buckets.length);
  {
    Iter$3016 $iterator = List$3016$iter(&(*(List$3017$subscript(&self->buckets, idx))));
    while (1) {
      auto $next = Iter$3016$next(&$iterator);
      if (!$next.index != 1) break;
      $tuple1171$137 pair = $next.Some.$0;
      {
        if ((interned$Interned$19$eq(pair.$0, search_key))) {
          return Some$137(pair.$1);
        }
      }
    }
  }
  return None$3230();
}
bool Option$137$is_some(Option$137 self) {
if (self.index == 0) {
{
    return true;
  }
}
  return false;
}
bool map$Map$1171_137$contains(map$Map$1171_137* self, interned$Interned$19 key) {
  return Option$137$is_some(map$Map$1171_137$get(self, key));
}
Option$3243 None$3244() {
  return  (Option$3243) { .index = 1};
}
Option$3243 Some$3243(parser$Variable* t) {
  return (Option$3243) {
.index = 0,
.Some = ($tuple3243) {.$0 = t}};
}
Option$3243 map$Map$1171_137$get_mut(map$Map$1171_137* self, interned$Interned$19 search_key) {
  if ((self->buckets.length == 0)) {
    return None$3244();
  }
  u64 idx  = (interned$Interned$19$hash(search_key) % self->buckets.length);
  {
    Iter$3016 $iterator = List$3016$iter(&(*(List$3017$subscript(&self->buckets, idx))));
    while (1) {
      auto $next = Iter$3016$next(&$iterator);
      if (!$next.index != 1) break;
      $tuple1171$137 pair = $next.Some.$0;
      {
        if ((interned$Interned$19$eq(pair.$0, search_key))) {
          return Some$3243((&pair.$1));
        }
      }
    }
  }
  return None$3244();
}
Option$3243 parser$Scope$get(parser$Scope* self, interned$Interned$19 name);
Option$3243 parser$Scope$get(parser$Scope* self, interned$Interned$19 name) {
  if (map$Map$1171_137$contains(&self->variables, name)) {
    return map$Map$1171_137$get_mut(&self->variables, name);
  }
if (self->parent.index == 0) {
parser$Scope* scope = (self->parent.Some.$0);
{
    return parser$Scope$get(scope, name);
  }
}
  return  (Option$3243) { .index = 1};
}
bool Option$3243$is_some(Option$3243 self) {
if (self.index == 0) {
{
    return true;
  }
}
  return false;
}
bool Option$3243$is_none(Option$3243 self) {
  return (!Option$3243$is_some(self));
}
typedef struct $tuple1171 $tuple1171;
u8* Field$get$1458(Field* self, $tuple1171* source) {
  return ((u8*)source + self->offset);
}
String fmt$format$1458(str fmt, $tuple1171 tuple, fmt$FormatOptions options) {
  if ((fmt.length == 0)) {
    String $defer$return$value = (String){0};
    return $defer$return$value;
  }
  fmt$StringBuilder builder = {};
  s32 value_index  = 0;
  List$37 fields  = _type_info.data[1458]->fields;
  if (List$37$is_empty(fields)) {
    return String$from$18((str) { .data = "()", .length = 2 });
  }
  while ((*fmt.data)) {
    if ((((*fmt.data) == 0x5c) && ((*(fmt.data + 1)) == 0x25))) {
      fmt$StringBuilder$append$5(&builder, 0x25);
      (fmt.data += 2);
      continue;
    }
    if ((((*fmt.data) == 0x25) && (value_index >= fields.length))) {
      panic((str) { .data = "too few data arguments provided to 'format'", .length = 43 });
    }
    if ((((*fmt.data) == 0x25) && (value_index < fields.length))) {
      Field field  = (*(List$37$subscript(&fields, value_index)));
      any value  = (any){
        .type = (Type*)field.type,
        .ptr = (void*)Field$get$1458(&field, (&tuple))};
      fmt$format_any(value, (&builder), options);
      value_index++;
    }
    else{
      fmt$StringBuilder$append$5(&builder, (u32)(*fmt.data));
    }
    fmt.data++;
  }
  String $defer$return$value = fmt$StringBuilder$get_string(&builder);
  fmt$StringBuilder$deinit(&builder);
  return $defer$return$value;
  fmt$StringBuilder$deinit(&builder);
}
void fmt$printlnf$1458(str fmt, $tuple1171 tuple) {
  String formatted  = fmt$format$1458(fmt, tuple, (*fmt$FormatOptions$current()));
  printf("%s\n", formatted.data);
  String$deinit(&formatted);
}
parser$Variable* Option$3243$unwrap(Option$3243 self) {
    auto $switch_target$25 = self;
if ($switch_target$25.index == 0) {
parser$Variable* v = ($switch_target$25.Some.$0);
{
    return v;
  }
}
else {
{
    panic((str) { .data = "unwrapped a 'none' option", .length = 25 });
  }
}
;
  parser$Variable* $default = {};
  return $default;
}
s32 analyzer$Analyzer$visit_identifier(analyzer$Analyzer* self, interned$Interned$19 identifier) {
  Option$3243 variable  = parser$Scope$get(self->current_scope, identifier);
  if (Option$3243$is_none(variable)) {
    fmt$printlnf$1458((str) { .data = "use of undeclared identifier %", .length = 30 }, ($tuple1171) {.$0 = identifier});
    exit(1);
    return (s32)(-1);
  }
  else{
    return Option$3243$unwrap(variable)->type;
  }
}
s32 analyzer$Analyzer$visit_expression(analyzer$Analyzer* self, parser$Expression* expression);
s32 analyzer$Analyzer$visit_unary(analyzer$Analyzer* self, parser$Expression* operand, s32 operator) {
  s32 operand_ty  = analyzer$Analyzer$visit_expression(self, operand);
  return operand_ty;
}
s32 analyzer$Analyzer$visit_binary(analyzer$Analyzer* self, parser$Expression* left, parser$Expression* right, s32 operator) {
  s32 left_ty  = analyzer$Analyzer$visit_expression(self, left);
  s32 right_ty  = analyzer$Analyzer$visit_expression(self, right);
  if ((operator == lexer$TType$Assign)) {
if (left->index == 1) {
interned$Interned$19 identifier = (left->Identifier.$0);
{
      (Option$3243$unwrap(parser$Scope$get(self->current_scope, identifier))->type = right_ty);
    }
}
  }
  return left_ty;
}
typedef struct Iter$3489 {
  parser$Expression** ptr;
  parser$Expression** end;
} Iter$3489;
Iter$3489 List$3489$iter(List$3489* self) {
  return (Iter$3489){
    .ptr = (parser$Expression**)self->data,
    .end = (parser$Expression**)(parser$Expression**)(self->data + self->length)};
}
typedef struct Option$3489 Option$3489;
typedef $tuple3489 Option$3489$Some;
typedef struct Option$3489 {
  int index;
  union {
    Option$3489$Some Some;
  };
} Option$3489;
typedef struct Iter$3489 Iter$3489;
Option$3489 Iter$3489$next(Iter$3489* self) {
  if ((self->ptr >= self->end)) {
    return  (Option$3489) { .index = 1};
  }
  Option$3489 value  = (Option$3489) {
.index = 0,
.Some = ($tuple3489) {.$0 = (*self->ptr)}};
  self->ptr++;
  return value;
}
typedef struct List$2791 List$2791;
void List$2791$resize(List$2791* self, u64 new_capacity) {
  if (((new_capacity < self->capacity) && (new_capacity < self->length))) {
    (self->length = new_capacity);
  }
  (self->capacity = new_capacity);
  if ((self->allocator == NULL)) {
    (self->allocator = get_default_allocator());
  }
  (self->data = Dyn_Allocator$resize(self->allocator, self->data, sizeof(s32), self->capacity));
}
void List$2791$push(List$2791* self, s32 v) {
  if (((self->length + 1) >= self->capacity)) {
    if ((self->capacity == 0)) {
      (self->capacity = 4);
    }
    List$2791$resize(self, (self->capacity * 2));
  }
  (self->data[self->length] = v);
  self->length++;
}
Option$2898 Some$2898($tuple2792$2791 t) {
  return (Option$2898) {
.index = 0,
.Some = ($tuple2898) {.$0 = t}};
}
s32 analyzer$Analyzer$visit_call(analyzer$Analyzer* self, interned$Interned$19 callee, List$3489 args) {
  parser$Variable* callee_variable  = Option$3243$unwrap(parser$Scope$get(self->current_scope, callee));
  if ((callee_variable->type != parser$BType$Function)) {
    (callee_variable->type = parser$BType$Function);
  }
  List$2791 arg_types  = (List$2791){0};
  s32 return_type = {0};
  {
    List$3489 $iterable = args;
    Iter$3489 $iterator = List$3489$iter(&$iterable);
    while (1) {
      auto $next = Iter$3489$next(&$iterator);
      if (!$next.index != 1) break;
      parser$Expression* arg = $next.Some.$0;
      {
        List$2791$push(&arg_types, analyzer$Analyzer$visit_expression(self, arg));
      }
    }
  }
  (return_type = parser$BType$Integer);
  (callee_variable->inferred_function_signature = Some$2898(($tuple2792$2791) {.$0 = arg_types, .$1 = return_type}));
  return return_type;
}
s32 analyzer$Analyzer$visit_expression(analyzer$Analyzer* self, parser$Expression* expression) {
    auto $switch_target$26 = expression;
if ($switch_target$26->index == 0) {
s64 integer = ($switch_target$26->Literal.$0);
{
    return parser$BType$Integer;
  }
}
  else if ($switch_target$26->index == 1) {
interned$Interned$19 identifier = ($switch_target$26->Identifier.$0);
{
    return analyzer$Analyzer$visit_identifier(self, identifier);
  }
}
  else if ($switch_target$26->index == 2) {
parser$Expression* operand = ($switch_target$26->Unary.$0);
lexer$TType operator = ($switch_target$26->Unary.$1);
{
    return analyzer$Analyzer$visit_unary(self, operand, operator);
  }
}
  else if ($switch_target$26->index == 3) {
parser$Expression* left = ($switch_target$26->Binary.$0);
parser$Expression* right = ($switch_target$26->Binary.$1);
lexer$TType operator = ($switch_target$26->Binary.$2);
{
    return analyzer$Analyzer$visit_binary(self, left, right, operator);
  }
}
  else if ($switch_target$26->index == 4) {
interned$Interned$19 callee = ($switch_target$26->Call.$0);
List$3489 args = ($switch_target$26->Call.$1);
{
    return analyzer$Analyzer$visit_call(self, callee, args);
  }
}
else {
{
    panic((str) { .data = "Unhandled expression type", .length = 25 });
  }
}
;
  return parser$BType$Integer;
}
void analyzer$Analyzer$visit_if(analyzer$Analyzer* self, parser$Expression* condition, parser$Block block) {
}
void analyzer$Analyzer$visit_statement(analyzer$Analyzer* self, parser$Statement* statement) {
    auto $switch_target$27 = statement;
if ($switch_target$27->index == 0) {
interned$Interned$19 identifier = ($switch_target$27->Extrn.$0);
{
    analyzer$Analyzer$visit_extrn(self, identifier);
  }
}
  else if ($switch_target$27->index == 1) {
interned$Interned$19 identifier = ($switch_target$27->Auto.$0);
{
    analyzer$Analyzer$visit_auto(self, identifier);
  }
}
  else if ($switch_target$27->index == 2) {
parser$Expression* expression = ($switch_target$27->Expression.$0);
{
    analyzer$Analyzer$visit_expression(self, expression);
  }
}
  else if ($switch_target$27->index == 3) {
parser$Expression* condition = ($switch_target$27->If.$0);
parser$Block block = ($switch_target$27->If.$1);
{
    analyzer$Analyzer$visit_if(self, condition, block);
  }
}
else {
{
    panic((str) { .data = "Unhandled statement type", .length = 24 });
  }
}
;
}
void analyzer$Analyzer$visit_block(analyzer$Analyzer* self, parser$Block block) {
  parser$Scope* old_scope  = self->current_scope;
  (block.scope.parent = Some$3003(self->current_scope));
  (self->current_scope = (&block.scope));
  {
    List$3382 $iterable = block.statements;
    Iter$3382 $iterator = List$3382$iter(&$iterable);
    while (1) {
      auto $next = Iter$3382$next(&$iterator);
      if (!$next.index != 1) break;
      parser$Statement* statement = $next.Some.$0;
      {
        analyzer$Analyzer$visit_statement(self, statement);
      }
    }
  }
  (self->current_scope = old_scope);
}
void analyzer$Analyzer$visit_function(analyzer$Analyzer* self, parser$Function function) {
  parser$Scope block_scope  = function.block.scope;
  {
    List$1171 $iterable = function.parameters;
    Iter$1171 $iterator = List$1171$iter(&$iterable);
    while (1) {
      auto $next = Iter$1171$next(&$iterator);
      if (!$next.index != 1) break;
      interned$Interned$19 parameter = $next.Some.$0;
      {
        parser$Scope$insert(&block_scope, parameter, None$3230());
      }
    }
  }
  analyzer$Analyzer$visit_block(self, function.block);
}
void analyzer$Analyzer$visit_program(analyzer$Analyzer* self, parser$Program program) {
  (self->current_scope = (&program.scope));
  {
    List$138 $iterable = program.functions;
    Iter$138 $iterator = List$138$iter(&$iterable);
    while (1) {
      auto $next = Iter$138$next(&$iterator);
      if (!$next.index != 1) break;
      parser$Function function = $next.Some.$0;
      {
        analyzer$Analyzer$visit_function(self, function);
      }
    }
  }
  (self->current_scope = NULL);
}
typedef struct llvm$LLVMOpaqueModule llvm$LLVMOpaqueModule;
typedef struct llvm$LLVMOpaqueContext llvm$LLVMOpaqueContext;
typedef struct llvm$LLVMOpaqueBuilder llvm$LLVMOpaqueBuilder;
typedef struct llvm$LLVMOpaqueTargetData llvm$LLVMOpaqueTargetData;
typedef struct llvm$LLVMTarget llvm$LLVMTarget;
typedef struct llvm$LLVMOpaqueTargetMachine llvm$LLVMOpaqueTargetMachine;
typedef struct emitter$Emitter {
  llvm$LLVMOpaqueModule* mod;
  llvm$LLVMOpaqueContext* ctx;
  llvm$LLVMOpaqueBuilder* builder;
  llvm$LLVMOpaqueTargetData* target_data;
  llvm$LLVMTarget* target;
  llvm$LLVMOpaqueTargetMachine* machine;
  parser$Scope* current_scope;
} emitter$Emitter;
extern llvm$LLVMOpaqueContext*  LLVMContextCreate();
extern llvm$LLVMOpaqueBuilder*  LLVMCreateBuilderInContext(llvm$LLVMOpaqueContext*);
extern llvm$LLVMOpaqueModule*  LLVMModuleCreateWithNameInContext(u8*, llvm$LLVMOpaqueContext*);
extern s32  LLVMInitializeNativeTarget();
extern u8*  LLVMGetDefaultTargetTriple();
extern u8*  LLVMGetHostCPUFeatures();
extern u8*  LLVMGetHostCPUName();
extern void  LLVMSetTarget(llvm$LLVMOpaqueModule*, u8*);
extern s32  LLVMGetTargetFromTriple(u8*, llvm$LLVMTarget**, u8**);
extern void  LLVMDisposeMessage(u8*);
typedef enum {
  llvm$LLVMCodeGenOptLevel$None = 0,
  llvm$LLVMCodeGenOptLevel$Less = 1,
  llvm$LLVMCodeGenOptLevel$Default = 2,
  llvm$LLVMCodeGenOptLevel$Aggressive = 3
} llvm$LLVMCodeGenOptLevel;
typedef enum {
  llvm$LLVMRelocMode$Default = 0,
  llvm$LLVMRelocMode$Static = 1,
  llvm$LLVMRelocMode$PIC = 2,
  llvm$LLVMRelocMode$DynamicNoPic = 3,
  llvm$LLVMRelocMode$ROPI = 4,
  llvm$LLVMRelocMode$RWPI = 5,
  llvm$LLVMRelocMode$ROPI_RWPI = 6
} llvm$LLVMRelocMode;
typedef enum {
  llvm$LLVMCodeModel$Default = 0,
  llvm$LLVMCodeModel$JITDefault = 1,
  llvm$LLVMCodeModel$Tiny = 2,
  llvm$LLVMCodeModel$Small = 3,
  llvm$LLVMCodeModel$Kernel = 4,
  llvm$LLVMCodeModel$Medium = 5,
  llvm$LLVMCodeModel$Large = 6
} llvm$LLVMCodeModel;
extern llvm$LLVMOpaqueTargetMachine*  LLVMCreateTargetMachine(llvm$LLVMTarget*, u8*, u8*, u8*, llvm$LLVMCodeGenOptLevel, llvm$LLVMRelocMode, llvm$LLVMCodeModel);
extern llvm$LLVMOpaqueTargetData*  LLVMCreateTargetDataLayout(llvm$LLVMOpaqueTargetMachine*);
emitter$Emitter emitter$Emitter$new() {
  llvm$LLVMOpaqueContext* ctx  = LLVMContextCreate();
  llvm$LLVMOpaqueBuilder* builder  = LLVMCreateBuilderInContext(ctx);
  llvm$LLVMOpaqueModule* mod  = LLVMModuleCreateWithNameInContext("b-compiler-module", ctx);
  LLVMInitializeNativeTarget();
  u8* target_triple  = LLVMGetDefaultTargetTriple();
  u8* features  = LLVMGetHostCPUFeatures();
  u8* cpu  = LLVMGetHostCPUName();
  LLVMSetTarget(mod, target_triple);
  llvm$LLVMTarget* target = {};
  u8* message = {0};
  if (LLVMGetTargetFromTriple(target_triple, (&target), (&message))) {
    printf("Error getting target from triple: %s\n", message);
    LLVMDisposeMessage((u8*)message);
    exit(1);
  }
  llvm$LLVMOpaqueTargetMachine* machine  = LLVMCreateTargetMachine(target, target_triple, cpu, features, llvm$LLVMCodeGenOptLevel$Default, llvm$LLVMRelocMode$PIC, llvm$LLVMCodeModel$Default);
  llvm$LLVMOpaqueTargetData* target_data  = LLVMCreateTargetDataLayout(machine);
  return (emitter$Emitter){
    .target_data = (llvm$LLVMOpaqueTargetData*)target_data,
    .target = (llvm$LLVMTarget*)target,
    .machine = (llvm$LLVMOpaqueTargetMachine*)machine,
    .mod = (llvm$LLVMOpaqueModule*)mod,
    .ctx = (llvm$LLVMOpaqueContext*)ctx,
    .builder = (llvm$LLVMOpaqueBuilder*)builder};
}
typedef struct emitter$Emitter emitter$Emitter;
void emitter$Emitter$visit_function(emitter$Emitter* self, parser$Function function) {
}
void emitter$Emitter$visit_program(emitter$Emitter* self, parser$Program program) {
  (self->current_scope = (&program.scope));
  {
    List$138 $iterable = program.functions;
    Iter$138 $iterator = List$138$iter(&$iterable);
    while (1) {
      auto $next = Iter$138$next(&$iterator);
      if (!$next.index != 1) break;
      parser$Function function = $next.Some.$0;
      {
        emitter$Emitter$visit_function(self, function);
      }
    }
  }
  (self->current_scope = NULL);
}
void __ela_main_()
{
  elexify$Lexer lexer  = elexify$Lexer$new(Some$1481(lexer$operators()), Some$1481(lexer$keywords()), Some$1716((List$18){0}));
  elexify$State state  = elexify$State$from_file$18((str) { .data = "sample.b", .length = 8 });
  elexify$Lexer$push_state(&lexer, state);
  parser$Program program  = parser$parse_program((&lexer));
  analyzer$Analyzer analyzer = {};
  analyzer$Analyzer$visit_program(&analyzer, program);
  emitter$Emitter emitter  = emitter$Emitter$new();
  emitter$Emitter$visit_program(&emitter, program);
}
typedef struct Slice$5 {
  u32* data;
  u64 length;
} Slice$5;
Slice$5 u32$as_char_slice(u32 self) {
  static u32 chars[2] = {0x0, 0x0};
  (chars[0] = self);
  return (Slice$5){
    .data = (u32*)chars,
    .length = (u64)1};
}
u64 u32$hash(u32 self) {
  u64 hash  = HASH_INITIAL_VALUE;
  (hash ^= self);
  (hash *= HASH_FACTOR);
  return hash;
}
u32 u32$min_value() {
  return 0;
}
Slice$5 String$as_char_slice(String self) {
  return (Slice$5){
    .data = (u32*)self.data,
    .length = (u64)(self.length / 4)};
}
Iter$7 String$iter_mut(String* self) {
  return (Iter$7){
    .ptr = (u8*)self->data,
    .end = (u8*)(self->data + self->length)};
}
Iter$7 String$iter(String* self) {
  return (Iter$7){
    .ptr = (u8*)self->data,
    .end = (u8*)(self->data + self->length)};
}
typedef struct fmt$UTF8_Iter {
  Slice$7 slice;
  u32 position;
  u32 current_char;
} fmt$UTF8_Iter;
fmt$UTF8_Iter String$chars(String self) {
  return (fmt$UTF8_Iter){
    .slice = (Slice$7)String$as_byte_slice(self),
    .position = (u32)0,
    .current_char = (u32)0x0};
}
typedef struct SliceMut$7 {
  u8* data;
  u64 length;
} SliceMut$7;
SliceMut$7 String$slice_mut(String self, RangeBase$1 range) {
  return (SliceMut$7){
    .data = (u8*)(u8*)(self.data + range.begin),
    .length = (u64)(range.end - range.begin)};
}
Slice$7 String$slice(String self, RangeBase$1 range) {
  return (Slice$7){
    .data = (u8*)(self.data + range.begin),
    .length = (u64)(range.end - range.begin)};
}
u8 String$pop(String* self) {
  if ((self->length == 0)) {
    return (u8)0x0;
  }
  u8 ch  = self->data[self->length--];
  (self->data[self->length] = 0x0);
  return ch;
}
void* Dyn_Allocator$allocate_array(Dyn_Allocator* self, u64 size, u64 n) {
  void*(*p_allocate_array)(void*, u64, u64) = self->p_allocate_array;
  return p_allocate_array(self->instance, size, n);
}
void Dyn_Allocator$deinit(Dyn_Allocator* self) {
  void(*p_deinit)(void*) = self->p_deinit;
  p_deinit(self->instance);
}
void* Dyn_Allocator$allocate(Dyn_Allocator* self, u64 size) {
  void*(*p_allocate)(void*, u64) = self->p_allocate;
  return p_allocate(self->instance, size);
}
extern s32  isspace(s32);
bool String$is_empty_or_whitespace(String self) {
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = self.length};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 i = $next.Some.$0;
      {
        u8 ch  = self.data[i];
        if ((!isspace(ch))) {
          return false;
        }
      }
    }
  }
  return true;
}
u64 u64$max_value() {
  return 18446744073709551615;
}
u64 u64$min_value() {
  return 0;
}
u64 u8$hash(u8 self) {
  u64 hash  = HASH_INITIAL_VALUE;
  (hash ^= self);
  (hash *= HASH_FACTOR);
  return hash;
}
u8 u8$max_value() {
  return 255;
}
u8 u8$min_value() {
  return 0;
}
u8* String$subscript_mut(String* self, u64 idx) {
  return (&self->data[idx]);
}
String String$empty() {
  return (String){0};
}
Option$7 None$370() {
  return  (Option$7) { .index = 1};
}
Option$7 Some$7(u8 t) {
  return (Option$7) {
.index = 0,
.Some = ($tuple7) {.$0 = t}};
}
Option$7 String$back(String self) {
  if ((self.length == 0)) {
    return None$370();
  }
  return Some$7(self.data[(self.length - 1)]);
}
void String$insert_at(String* self, u64 index, u8 ch) {
  if ((index > self->length)) {
    return;
  }
  if ((self->capacity == 0)) {
    (self->capacity = (256 / 3));
  }
  if (((!self->data) || ((self->length + 1) >= self->capacity))) {
    String$resize(self, (self->capacity * 3));
  }
  memmove(((self->data + index) + 1), (self->data + index), (self->length - index));
  (self->data[index] = ch);
  self->length++;
  (self->data[self->length] = 0x0);
}
bool String$neq(String self, String other) {
  return (!String$eq(self, other));
}
u8 String$pop_front(String* self) {
  if ((self->length == 0)) {
    return (u8)0x0;
  }
  u8 ch  = self->data[0];
  memmove(self->data, (self->data + 1), (self->length - 1));
  self->length--;
  (self->data[self->length] = 0x0);
  return ch;
}
void String$push_front(String* self, u8 ch) {
  if ((self->capacity == 0)) {
    (self->capacity = (256 / 3));
  }
  if (((self->length + 1) >= self->capacity)) {
    String$resize(self, (self->capacity * 3));
  }
  memmove((self->data + 1), self->data, self->length);
  (self->data[0] = ch);
  self->length++;
  (self->data[self->length] = 0x0);
}
Option$7 String$front(String self) {
  if ((self.length == 0)) {
    return None$370();
  }
  return Some$7(self.data[0]);
}
void String$erase_at(String* self, u64 index) {
  if ((index >= self->length)) {
    return;
  }
  memmove((self->data + index), ((self->data + index) + 1), ((self->length - index) - 1));
  self->length--;
  (self->data[self->length] = 0x0);
}
u64 s8$hash(s8 self) {
  u64 hash  = HASH_INITIAL_VALUE;
  (hash ^= self);
  (hash *= HASH_FACTOR);
  return hash;
}
s8 s8$max_value() {
  return 127;
}
s8 s8$min_value() {
  return (s8)(-128);
}
Slice$5 str$as_char_slice(str self) {
  return (Slice$5){
    .data = (u32*)self.data,
    .length = (u64)self.length};
}
bool str$neq(str self, str other) {
  return (!str$eq(self, other));
}
typedef struct IterMut$7 {
  u8* ptr;
  u8* end;
} IterMut$7;
IterMut$7 str$iter_mut(str* self) {
  return (IterMut$7){
    .ptr = (u8*)(u8*)self->data,
    .end = (u8*)(self->data + self->length)};
}
Option$7 str$back(str self) {
  if ((self.length == 0)) {
    return None$370();
  }
  return Some$7(self.data[(self.length - 1)]);
}
bool str$is_empty(str self) {
  return (self.length == 0);
}
str str$empty() {
  return (str){0};
}
Option$7 str$front(str self) {
  if ((self.length == 0)) {
    return None$370();
  }
  return Some$7(self.data[0]);
}
bool str$is_empty_or_whitespace(str self) {
  {
    RangeBase$1 $iterable = (RangeBase$1) {.begin = 0, .end = self.length};
    RangeIter$1 $iterator = RangeBase$1$iter(&$iterable);
    while (1) {
      auto $next = RangeIter$1$next(&$iterator);
      if (!$next.index != 1) break;
      s32 i = $next.Some.$0;
      {
        u8 ch  = self.data[i];
        if ((!isspace(ch))) {
          return false;
        }
      }
    }
  }
  return true;
}
typedef struct $tuple1$1 {
  s32 $0;
  s32 $1;
} $tuple1$1;
Slice$7 str$slice(str* self, RangeBase$1 range) {
$tuple1$1 $deconstruction$2 = ($tuple1$1) {.$0 = range.begin, .$1 = range.end};
auto start = $deconstruction$2.$0;
auto end = $deconstruction$2.$1;
  s32 length  = (end - start);
  if ((((start < 0) || (length < 0)) || ((start + length) > self->length))) {
    return (Slice$7){0};
  }
  return (Slice$7){
    .data = (u8*)(self->data + start),
    .length = (u64)length};
}
u8* str$subscript_mut(str* self, u64 idx) {
  return (&self->data[idx]);
}
u64 s16$hash(s16 self) {
  u64 hash  = HASH_INITIAL_VALUE;
  (hash ^= self);
  (hash *= HASH_FACTOR);
  return hash;
}
s16 s16$max_value() {
  return 32767;
}
s16 s16$min_value() {
  return (s16)(-32768);
}
fmt$FormatOptions fmt$FormatOptions$quoted(fmt$FormatOptions self) {
  fmt$FormatOptions copy  = self;
  (copy.quote_strings = true);
  return copy;
}
void interned$Interned$19$format(interned$Interned$19* self, fmt$StringBuilder* builder, fmt$FormatOptions options) {
  if (self->data) {
    fmt$StringBuilder$appendf$1075(builder, (str) { .data = "Interned { % }", .length = 14 }, ($tuple19) {.$0 = (*self->data)}, fmt$FormatOptions$quoted(options));
  }
  else{
    fmt$StringBuilder$append$18(builder, (str) { .data = "Interned { null }", .length = 17 });
  }
}
bool interned$Interned$19$neq(interned$Interned$19 self, interned$Interned$19 other) {
  return (self.data != other.data);
}
String interned$Interned$19$value(interned$Interned$19 self) {
  return (*self.data);
}
Slice$7 Slice$7$from(u8* data, u32 len) {
  return (Slice$7){
    .data = (u8*)data,
    .length = (u64)len};
}
Slice$7 Slice$7$as_byte_slice(Slice$7 self) {
  return self;
}
void fmt$StringBuilder$append$360(fmt$StringBuilder* self, Slice$7 value) {
  Slice$7 slice  = Slice$7$as_byte_slice(value);
  if ((slice.length <= 0)) {
    return;
  }
  if ((!self->root)) {
    (self->root = fmt$StringBuilderBlock$new());
    (self->current = self->root);
  }
  s32 slice_index  = 0;
  u64 length  = slice.length;
  if (((length == 1) && (slice.data[0] == 0x0))) {
    return;
  }
  s32 remaining  = (fmt$STRING_BUILDER_BLOCK_MAX_LEN - self->current->length);
  while ((length > 0)) {
    if ((length <= remaining)) {
      memcpy((self->current->data + self->current->length), slice.data, length);
      (self->current->length += length);
      break;
    }
    if (((self->current->data != NULL) && (slice.data != NULL))) {
      memcpy((self->current->data + self->current->length), (slice.data + slice_index), remaining);
      (self->current->length += remaining);
    }
    (slice_index += remaining);
    (length -= remaining);
    (self->current->next = fmt$StringBuilderBlock$new());
    (self->current = self->current->next);
    (remaining = fmt$STRING_BUILDER_BLOCK_MAX_LEN);
  }
}
void s32$format(s32* self, fmt$StringBuilder* builder, fmt$FormatOptions options) {
  u8 buffer[32] = {0};
  s32 len  = snprintf(buffer, 32, "%d", (*self));
  fmt$StringBuilder$append$360(builder, Slice$7$from(buffer, len));
}
u64 s32$hash(s32 self) {
  u64 hash  = HASH_INITIAL_VALUE;
  (hash ^= self);
  (hash *= HASH_FACTOR);
  return hash;
}
s32 s32$max_value() {
  return 2147483647;
}
s32 s32$min_value() {
  return (s32)(-2147483648);
}
u64 s64$hash(s64 self) {
  u64 hash  = HASH_INITIAL_VALUE;
  (hash ^= self);
  (hash *= HASH_FACTOR);
  return hash;
}
s64 s64$max_value() {
  return 9223372036854775807;
}
s64 s64$min_value() {
  return (s64)(-9223372036854775808);
}
u64 f32$hash(f32 self) {
  u64 hash  = HASH_INITIAL_VALUE;
  (hash ^= (u32)self);
  (hash *= HASH_FACTOR);
  return hash;
}
f32 f32$max_value() {
  return 340282350000000000000000000000000000000.0f;
}
f32 f32$min_value() {
  return (f32)(-340282350000000000000000000000000000000.0f);
}
u64 u16$hash(u16 self) {
  u64 hash  = HASH_INITIAL_VALUE;
  (hash ^= self);
  (hash *= HASH_FACTOR);
  return hash;
}
u16 u16$max_value() {
  return 65535;
}
u16 u16$min_value() {
  return 0;
}
u64 f64$hash(f64 self) {
  u64 hash  = HASH_INITIAL_VALUE;
  (hash ^= (u32)self);
  (hash *= HASH_FACTOR);
  return hash;
}
f64 f64$max_value() {
  return 179769313486231570000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0;
}
f64 f64$min_value() {
  return (f64)(-179769313486231570000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0);
}
List$146 _type_info = {};

void $initialize_reflection_system() {
_type_info.length = _type_info.capacity = 55;
_type_info.data = calloc(sizeof(Type*), 3664);_type_info.data[11]= malloc(sizeof(Type));
*_type_info.data[11] = (Type){ .id = 11, .name = (str){.data="void", .length = 4}, .size = sizeof(void), .flags = 0
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[11]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[11]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[11]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[14]= malloc(sizeof(Type));
*_type_info.data[14] = (Type){ .id = 14, .name = (str){.data="IsPointer", .length = 9}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[14]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[14]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[13]= malloc(sizeof(Type));
*_type_info.data[13] = (Type){ .id = 13, .name = (str){.data="IsMutPointer", .length = 12}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[13]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[13]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[152]= malloc(sizeof(Type));
*_type_info.data[152] = (Type){ .id = 152, .name = (str){.data="*mut void", .length = 9}, .size = sizeof(void*), .flags = 1024
,
.element_type = _type_info.data[11],
 };{};
{ auto args = &_type_info.data[152]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[152]->interfaces.data = malloc(2 * sizeof(Type));
_type_info.data[152]->interfaces.length = 2;
_type_info.data[152]->interfaces.capacity = 2;
_type_info.data[152]->interfaces.data[0] = _type_info.data[14];
_type_info.data[152]->interfaces.data[1] = _type_info.data[13];
;
{ auto args = &_type_info.data[152]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[170]= malloc(sizeof(Type));
*_type_info.data[170] = (Type){ .id = 170, .name = (str){.data="IsNumeric", .length = 9}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[170]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[170]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[172]= malloc(sizeof(Type));
*_type_info.data[172] = (Type){ .id = 172, .name = (str){.data="IsInteger", .length = 9}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[172]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[172]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[163]= malloc(sizeof(Type));
*_type_info.data[163] = (Type){ .id = 163, .name = (str){.data="Hash", .length = 4}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[163]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[163]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[7]= malloc(sizeof(Type));
*_type_info.data[7] = (Type){ .id = 7, .name = (str){.data="u8", .length = 2}, .size = sizeof(u8), .flags = 4097
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[7]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[7]->interfaces.data = malloc(3 * sizeof(Type));
_type_info.data[7]->interfaces.length = 3;
_type_info.data[7]->interfaces.capacity = 3;
_type_info.data[7]->interfaces.data[0] = _type_info.data[170];
_type_info.data[7]->interfaces.data[1] = _type_info.data[172];
_type_info.data[7]->interfaces.data[2] = _type_info.data[163];
_type_info.data[7]->methods.data = malloc(1 * sizeof(Type));
_type_info.data[7]->methods.length = 1;
_type_info.data[7]->methods.capacity = 1;
_type_info.data[7]->methods.data[0].$0 = (str){.data="hash", .length= 4};
_type_info.data[7]->methods.data[0].$1 = u8$hash;
;
_type_info.data[2]= malloc(sizeof(Type));
*_type_info.data[2] = (Type){ .id = 2, .name = (str){.data="s16", .length = 3}, .size = sizeof(s16), .flags = 2049
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[2]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[2]->interfaces.data = malloc(3 * sizeof(Type));
_type_info.data[2]->interfaces.length = 3;
_type_info.data[2]->interfaces.capacity = 3;
_type_info.data[2]->interfaces.data[0] = _type_info.data[170];
_type_info.data[2]->interfaces.data[1] = _type_info.data[172];
_type_info.data[2]->interfaces.data[2] = _type_info.data[163];
_type_info.data[2]->methods.data = malloc(1 * sizeof(Type));
_type_info.data[2]->methods.length = 1;
_type_info.data[2]->methods.capacity = 1;
_type_info.data[2]->methods.data[0].$0 = (str){.data="hash", .length= 4};
_type_info.data[2]->methods.data[0].$1 = s16$hash;
;
_type_info.data[764]= malloc(sizeof(Type));
*_type_info.data[764] = (Type){ .id = 764, .name = (str){.data="Format", .length = 6}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[764]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[764]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[1]= malloc(sizeof(Type));
*_type_info.data[1] = (Type){ .id = 1, .name = (str){.data="s32", .length = 3}, .size = sizeof(s32), .flags = 2049
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[1]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[1]->interfaces.data = malloc(4 * sizeof(Type));
_type_info.data[1]->interfaces.length = 4;
_type_info.data[1]->interfaces.capacity = 4;
_type_info.data[1]->interfaces.data[0] = _type_info.data[170];
_type_info.data[1]->interfaces.data[1] = _type_info.data[172];
_type_info.data[1]->interfaces.data[2] = _type_info.data[163];
_type_info.data[1]->interfaces.data[3] = _type_info.data[764];
_type_info.data[1]->methods.data = malloc(2 * sizeof(Type));
_type_info.data[1]->methods.length = 2;
_type_info.data[1]->methods.capacity = 2;
_type_info.data[1]->methods.data[0].$0 = (str){.data="format", .length= 6};
_type_info.data[1]->methods.data[0].$1 = s32$format;
_type_info.data[1]->methods.data[1].$0 = (str){.data="hash", .length= 4};
_type_info.data[1]->methods.data[1].$1 = s32$hash;
;
_type_info.data[0]= malloc(sizeof(Type));
*_type_info.data[0] = (Type){ .id = 0, .name = (str){.data="s64", .length = 3}, .size = sizeof(s64), .flags = 2049
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[0]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[0]->interfaces.data = malloc(3 * sizeof(Type));
_type_info.data[0]->interfaces.length = 3;
_type_info.data[0]->interfaces.capacity = 3;
_type_info.data[0]->interfaces.data[0] = _type_info.data[170];
_type_info.data[0]->interfaces.data[1] = _type_info.data[172];
_type_info.data[0]->interfaces.data[2] = _type_info.data[163];
_type_info.data[0]->methods.data = malloc(1 * sizeof(Type));
_type_info.data[0]->methods.length = 1;
_type_info.data[0]->methods.capacity = 1;
_type_info.data[0]->methods.data[0].$0 = (str){.data="hash", .length= 4};
_type_info.data[0]->methods.data[0].$1 = s64$hash;
;
_type_info.data[6]= malloc(sizeof(Type));
*_type_info.data[6] = (Type){ .id = 6, .name = (str){.data="u16", .length = 3}, .size = sizeof(u16), .flags = 4097
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[6]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[6]->interfaces.data = malloc(3 * sizeof(Type));
_type_info.data[6]->interfaces.length = 3;
_type_info.data[6]->interfaces.capacity = 3;
_type_info.data[6]->interfaces.data[0] = _type_info.data[170];
_type_info.data[6]->interfaces.data[1] = _type_info.data[172];
_type_info.data[6]->interfaces.data[2] = _type_info.data[163];
_type_info.data[6]->methods.data = malloc(1 * sizeof(Type));
_type_info.data[6]->methods.length = 1;
_type_info.data[6]->methods.capacity = 1;
_type_info.data[6]->methods.data[0].$0 = (str){.data="hash", .length= 4};
_type_info.data[6]->methods.data[0].$1 = u16$hash;
;
_type_info.data[165]= malloc(sizeof(Type));
*_type_info.data[165] = (Type){ .id = 165, .name = (str){.data="AsCharSlice", .length = 11}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[165]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[165]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[166]= malloc(sizeof(Type));
*_type_info.data[166] = (Type){ .id = 166, .name = (str){.data="AsByteSlice", .length = 11}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[166]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[166]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[5]= malloc(sizeof(Type));
*_type_info.data[5] = (Type){ .id = 5, .name = (str){.data="u32", .length = 3}, .size = sizeof(u32), .flags = 4097
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[5]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[5]->interfaces.data = malloc(5 * sizeof(Type));
_type_info.data[5]->interfaces.length = 5;
_type_info.data[5]->interfaces.capacity = 5;
_type_info.data[5]->interfaces.data[0] = _type_info.data[170];
_type_info.data[5]->interfaces.data[1] = _type_info.data[172];
_type_info.data[5]->interfaces.data[2] = _type_info.data[163];
_type_info.data[5]->interfaces.data[3] = _type_info.data[165];
_type_info.data[5]->interfaces.data[4] = _type_info.data[166];
_type_info.data[5]->methods.data = malloc(4 * sizeof(Type));
_type_info.data[5]->methods.length = 4;
_type_info.data[5]->methods.capacity = 4;
_type_info.data[5]->methods.data[0].$0 = (str){.data="to_precedence", .length= 13};
_type_info.data[5]->methods.data[0].$1 = u32$to_precedence;
_type_info.data[5]->methods.data[1].$0 = (str){.data="as_byte_slice", .length= 13};
_type_info.data[5]->methods.data[1].$1 = u32$as_byte_slice;
_type_info.data[5]->methods.data[2].$0 = (str){.data="as_char_slice", .length= 13};
_type_info.data[5]->methods.data[2].$1 = u32$as_char_slice;
_type_info.data[5]->methods.data[3].$0 = (str){.data="hash", .length= 4};
_type_info.data[5]->methods.data[3].$1 = u32$hash;
;
_type_info.data[4]= malloc(sizeof(Type));
*_type_info.data[4] = (Type){ .id = 4, .name = (str){.data="u64", .length = 3}, .size = sizeof(u64), .flags = 4097
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[4]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[4]->interfaces.data = malloc(3 * sizeof(Type));
_type_info.data[4]->interfaces.length = 3;
_type_info.data[4]->interfaces.capacity = 3;
_type_info.data[4]->interfaces.data[0] = _type_info.data[170];
_type_info.data[4]->interfaces.data[1] = _type_info.data[172];
_type_info.data[4]->interfaces.data[2] = _type_info.data[163];
_type_info.data[4]->methods.data = malloc(1 * sizeof(Type));
_type_info.data[4]->methods.length = 1;
_type_info.data[4]->methods.capacity = 1;
_type_info.data[4]->methods.data[0].$0 = (str){.data="hash", .length= 4};
_type_info.data[4]->methods.data[0].$1 = u64$hash;
;
_type_info.data[171]= malloc(sizeof(Type));
*_type_info.data[171] = (Type){ .id = 171, .name = (str){.data="IsFloat", .length = 7}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[171]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[171]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[9]= malloc(sizeof(Type));
*_type_info.data[9] = (Type){ .id = 9, .name = (str){.data="f32", .length = 3}, .size = sizeof(f32), .flags = 2
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[9]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[9]->interfaces.data = malloc(3 * sizeof(Type));
_type_info.data[9]->interfaces.length = 3;
_type_info.data[9]->interfaces.capacity = 3;
_type_info.data[9]->interfaces.data[0] = _type_info.data[170];
_type_info.data[9]->interfaces.data[1] = _type_info.data[171];
_type_info.data[9]->interfaces.data[2] = _type_info.data[163];
_type_info.data[9]->methods.data = malloc(1 * sizeof(Type));
_type_info.data[9]->methods.length = 1;
_type_info.data[9]->methods.capacity = 1;
_type_info.data[9]->methods.data[0].$0 = (str){.data="hash", .length= 4};
_type_info.data[9]->methods.data[0].$1 = f32$hash;
;
_type_info.data[8]= malloc(sizeof(Type));
*_type_info.data[8] = (Type){ .id = 8, .name = (str){.data="f64", .length = 3}, .size = sizeof(f64), .flags = 2
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[8]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[8]->interfaces.data = malloc(3 * sizeof(Type));
_type_info.data[8]->interfaces.length = 3;
_type_info.data[8]->interfaces.capacity = 3;
_type_info.data[8]->interfaces.data[0] = _type_info.data[170];
_type_info.data[8]->interfaces.data[1] = _type_info.data[171];
_type_info.data[8]->interfaces.data[2] = _type_info.data[163];
_type_info.data[8]->methods.data = malloc(1 * sizeof(Type));
_type_info.data[8]->methods.length = 1;
_type_info.data[8]->methods.capacity = 1;
_type_info.data[8]->methods.data[0].$0 = (str){.data="hash", .length= 4};
_type_info.data[8]->methods.data[0].$1 = f64$hash;
;
_type_info.data[3]= malloc(sizeof(Type));
*_type_info.data[3] = (Type){ .id = 3, .name = (str){.data="s8", .length = 2}, .size = sizeof(s8), .flags = 2049
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[3]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[3]->interfaces.data = malloc(3 * sizeof(Type));
_type_info.data[3]->interfaces.length = 3;
_type_info.data[3]->interfaces.capacity = 3;
_type_info.data[3]->interfaces.data[0] = _type_info.data[170];
_type_info.data[3]->interfaces.data[1] = _type_info.data[172];
_type_info.data[3]->interfaces.data[2] = _type_info.data[163];
_type_info.data[3]->methods.data = malloc(1 * sizeof(Type));
_type_info.data[3]->methods.length = 1;
_type_info.data[3]->methods.capacity = 1;
_type_info.data[3]->methods.data[0].$0 = (str){.data="hash", .length= 4};
_type_info.data[3]->methods.data[0].$1 = s8$hash;
;
_type_info.data[10]= malloc(sizeof(Type));
*_type_info.data[10] = (Type){ .id = 10, .name = (str){.data="bool", .length = 4}, .size = sizeof(bool), .flags = 4
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[10]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[10]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[10]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[151]= malloc(sizeof(Type));
*_type_info.data[151] = (Type){ .id = 151, .name = (str){.data="*mut u8", .length = 7}, .size = sizeof(void*), .flags = 1024
,
.element_type = _type_info.data[7],
 };{};
{ auto args = &_type_info.data[151]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[151]->interfaces.data = malloc(2 * sizeof(Type));
_type_info.data[151]->interfaces.length = 2;
_type_info.data[151]->interfaces.capacity = 2;
_type_info.data[151]->interfaces.data[0] = _type_info.data[14];
_type_info.data[151]->interfaces.data[1] = _type_info.data[13];
;
{ auto args = &_type_info.data[151]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[236]= malloc(sizeof(Type));
*_type_info.data[236] = (Type){ .id = 236, .name = (str){.data="fn  (*mut void, u64) -> *mut void", .length = 33}, .flags = 512
,
.element_type = NULL,
 };;
{ auto args = &_type_info.data[236]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[236]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[236]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[237]= malloc(sizeof(Type));
*_type_info.data[237] = (Type){ .id = 237, .name = (str){.data="fn *mut (*mut void, u64) -> *mut void", .length = 37}, .flags = 1536
,
.element_type = _type_info.data[236],
 };;
{ auto args = &_type_info.data[237]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[237]->interfaces.data = malloc(2 * sizeof(Type));
_type_info.data[237]->interfaces.length = 2;
_type_info.data[237]->interfaces.capacity = 2;
_type_info.data[237]->interfaces.data[0] = _type_info.data[14];
_type_info.data[237]->interfaces.data[1] = _type_info.data[13];
;
{ auto args = &_type_info.data[237]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[238]= malloc(sizeof(Type));
*_type_info.data[238] = (Type){ .id = 238, .name = (str){.data="fn  (*mut void, *const void) -> void", .length = 36}, .flags = 512
,
.element_type = NULL,
 };;
{ auto args = &_type_info.data[238]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[238]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[238]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[239]= malloc(sizeof(Type));
*_type_info.data[239] = (Type){ .id = 239, .name = (str){.data="fn *mut (*mut void, *const void) -> void", .length = 40}, .flags = 1536
,
.element_type = _type_info.data[238],
 };;
{ auto args = &_type_info.data[239]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[239]->interfaces.data = malloc(2 * sizeof(Type));
_type_info.data[239]->interfaces.length = 2;
_type_info.data[239]->interfaces.capacity = 2;
_type_info.data[239]->interfaces.data[0] = _type_info.data[14];
_type_info.data[239]->interfaces.data[1] = _type_info.data[13];
;
{ auto args = &_type_info.data[239]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[240]= malloc(sizeof(Type));
*_type_info.data[240] = (Type){ .id = 240, .name = (str){.data="fn  (*mut void, u64, u64) -> *mut void", .length = 38}, .flags = 512
,
.element_type = NULL,
 };;
{ auto args = &_type_info.data[240]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[240]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[240]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[241]= malloc(sizeof(Type));
*_type_info.data[241] = (Type){ .id = 241, .name = (str){.data="fn *mut (*mut void, u64, u64) -> *mut void", .length = 42}, .flags = 1536
,
.element_type = _type_info.data[240],
 };;
{ auto args = &_type_info.data[241]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[241]->interfaces.data = malloc(2 * sizeof(Type));
_type_info.data[241]->interfaces.length = 2;
_type_info.data[241]->interfaces.capacity = 2;
_type_info.data[241]->interfaces.data[0] = _type_info.data[14];
_type_info.data[241]->interfaces.data[1] = _type_info.data[13];
;
{ auto args = &_type_info.data[241]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[242]= malloc(sizeof(Type));
*_type_info.data[242] = (Type){ .id = 242, .name = (str){.data="fn  (*mut void, *const void, u64, u64) -> *mut void", .length = 51}, .flags = 512
,
.element_type = NULL,
 };;
{ auto args = &_type_info.data[242]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[242]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[242]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[243]= malloc(sizeof(Type));
*_type_info.data[243] = (Type){ .id = 243, .name = (str){.data="fn *mut (*mut void, *const void, u64, u64) -> *mut void", .length = 55}, .flags = 1536
,
.element_type = _type_info.data[242],
 };;
{ auto args = &_type_info.data[243]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[243]->interfaces.data = malloc(2 * sizeof(Type));
_type_info.data[243]->interfaces.length = 2;
_type_info.data[243]->interfaces.capacity = 2;
_type_info.data[243]->interfaces.data[0] = _type_info.data[14];
_type_info.data[243]->interfaces.data[1] = _type_info.data[13];
;
{ auto args = &_type_info.data[243]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[244]= malloc(sizeof(Type));
*_type_info.data[244] = (Type){ .id = 244, .name = (str){.data="fn  (*mut void) -> void", .length = 23}, .flags = 512
,
.element_type = NULL,
 };;
{ auto args = &_type_info.data[244]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[244]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[244]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[245]= malloc(sizeof(Type));
*_type_info.data[245] = (Type){ .id = 245, .name = (str){.data="fn *mut (*mut void) -> void", .length = 27}, .flags = 1536
,
.element_type = _type_info.data[244],
 };;
{ auto args = &_type_info.data[245]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[245]->interfaces.data = malloc(2 * sizeof(Type));
_type_info.data[245]->interfaces.length = 2;
_type_info.data[245]->interfaces.capacity = 2;
_type_info.data[245]->interfaces.data[0] = _type_info.data[14];
_type_info.data[245]->interfaces.data[1] = _type_info.data[13];
;
{ auto args = &_type_info.data[245]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[34]= malloc(sizeof(Type));
*_type_info.data[34] = (Type){ .id = 34, .name = (str){.data="Dyn_Allocator", .length = 13}, .size = sizeof(Dyn_Allocator), .flags = 16
,
.element_type = NULL,
 };_type_info.data[34]->fields.data = malloc(7 * sizeof(Field));
_type_info.data[34]->fields.length = 7;
_type_info.data[34]->fields.capacity = 7;
_type_info.data[34]->fields.data[0] = (Field) { .name = (str){.data="instance", .length=8}, .type = _type_info.data[152], .size = sizeof(void*),  };
_type_info.data[34]->fields.data[1] = (Field) { .name = (str){.data="p_allocate", .length=10}, .type = _type_info.data[237], .size = sizeof(void*),  };
_type_info.data[34]->fields.data[2] = (Field) { .name = (str){.data="p_free", .length=6}, .type = _type_info.data[239], .size = sizeof(void*),  };
_type_info.data[34]->fields.data[3] = (Field) { .name = (str){.data="p_allocate_array", .length=16}, .type = _type_info.data[241], .size = sizeof(void*),  };
_type_info.data[34]->fields.data[4] = (Field) { .name = (str){.data="p_resize", .length=8}, .type = _type_info.data[243], .size = sizeof(void*),  };
_type_info.data[34]->fields.data[5] = (Field) { .name = (str){.data="p_copy", .length=6}, .type = _type_info.data[243], .size = sizeof(void*),  };
_type_info.data[34]->fields.data[6] = (Field) { .name = (str){.data="p_deinit", .length=8}, .type = _type_info.data[245], .size = sizeof(void*),  };
;
{ auto args = &_type_info.data[34]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[34]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[34]->methods.data = malloc(7 * sizeof(Type));
_type_info.data[34]->methods.length = 7;
_type_info.data[34]->methods.capacity = 7;
_type_info.data[34]->methods.data[0].$0 = (str){.data="allocate_array", .length= 14};
_type_info.data[34]->methods.data[0].$1 = Dyn_Allocator$allocate_array;
_type_info.data[34]->methods.data[1].$0 = (str){.data="copy", .length= 4};
_type_info.data[34]->methods.data[1].$1 = Dyn_Allocator$copy;
_type_info.data[34]->methods.data[2].$0 = (str){.data="deinit", .length= 6};
_type_info.data[34]->methods.data[2].$1 = Dyn_Allocator$deinit;
_type_info.data[34]->methods.data[3].$0 = (str){.data="allocate", .length= 8};
_type_info.data[34]->methods.data[3].$1 = Dyn_Allocator$allocate;
_type_info.data[34]->methods.data[4].$0 = (str){.data="free", .length= 4};
_type_info.data[34]->methods.data[4].$1 = Dyn_Allocator$free;
_type_info.data[34]->methods.data[5].$0 = (str){.data="resize", .length= 6};
_type_info.data[34]->methods.data[5].$1 = Dyn_Allocator$resize;
;
_type_info.data[149]= malloc(sizeof(Type));
*_type_info.data[149] = (Type){ .id = 149, .name = (str){.data="*mut Dyn_Allocator", .length = 18}, .size = sizeof(void*), .flags = 1040
,
.element_type = _type_info.data[34],
 };{};
{ auto args = &_type_info.data[149]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[149]->interfaces.data = malloc(2 * sizeof(Type));
_type_info.data[149]->interfaces.length = 2;
_type_info.data[149]->interfaces.capacity = 2;
_type_info.data[149]->interfaces.data[0] = _type_info.data[14];
_type_info.data[149]->interfaces.data[1] = _type_info.data[13];
;
{ auto args = &_type_info.data[149]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[382]= malloc(sizeof(Type));
*_type_info.data[382] = (Type){ .id = 382, .name = (str){.data="StringUtils", .length = 11}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[382]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[382]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[154]= malloc(sizeof(Type));
*_type_info.data[154] = (Type){ .id = 154, .name = (str){.data="Clone", .length = 5}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[154]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[154]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[161]= malloc(sizeof(Type));
*_type_info.data[161] = (Type){ .id = 161, .name = (str){.data="Deinit", .length = 6}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[161]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[161]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[361]= malloc(sizeof(Type));
*_type_info.data[361] = (Type){ .id = 361, .name = (str){.data="Subscript!<u8>", .length = 14}, .flags = 8192
,
.element_type = NULL,
 };{}_type_info.data[361]->generic_args.data = malloc(1 * sizeof(Type));
_type_info.data[361]->generic_args.length = 1;
_type_info.data[361]->generic_args.capacity = 1;
_type_info.data[361]->generic_args.data[0] = _type_info.data[7];
;
{ auto args = &_type_info.data[361]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[158]= malloc(sizeof(Type));
*_type_info.data[158] = (Type){ .id = 158, .name = (str){.data="Eq", .length = 2}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[158]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[158]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[169]= malloc(sizeof(Type));
*_type_info.data[169] = (Type){ .id = 169, .name = (str){.data="Iterable", .length = 8}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[169]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[169]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[19]= malloc(sizeof(Type));
*_type_info.data[19] = (Type){ .id = 19, .name = (str){.data="String", .length = 6}, .size = sizeof(String), .flags = 16
,
.element_type = NULL,
 };_type_info.data[19]->fields.data = malloc(4 * sizeof(Field));
_type_info.data[19]->fields.length = 4;
_type_info.data[19]->fields.capacity = 4;
_type_info.data[19]->fields.data[0] = (Field) { .name = (str){.data="data", .length=4}, .type = _type_info.data[151], .size = sizeof(void*),  };
_type_info.data[19]->fields.data[1] = (Field) { .name = (str){.data="length", .length=6}, .type = _type_info.data[4], .size = sizeof(u64), .offset = offsetof(String, length) };
_type_info.data[19]->fields.data[2] = (Field) { .name = (str){.data="capacity", .length=8}, .type = _type_info.data[4], .size = sizeof(u64), .offset = offsetof(String, capacity) };
_type_info.data[19]->fields.data[3] = (Field) { .name = (str){.data="allocator", .length=9}, .type = _type_info.data[149], .size = sizeof(void*),  };
;
{ auto args = &_type_info.data[19]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[19]->interfaces.data = malloc(9 * sizeof(Type));
_type_info.data[19]->interfaces.length = 9;
_type_info.data[19]->interfaces.capacity = 9;
_type_info.data[19]->interfaces.data[0] = _type_info.data[382];
_type_info.data[19]->interfaces.data[1] = _type_info.data[154];
_type_info.data[19]->interfaces.data[2] = _type_info.data[161];
_type_info.data[19]->interfaces.data[3] = _type_info.data[361];
_type_info.data[19]->interfaces.data[4] = _type_info.data[158];
_type_info.data[19]->interfaces.data[5] = _type_info.data[169];
_type_info.data[19]->interfaces.data[6] = _type_info.data[165];
_type_info.data[19]->interfaces.data[7] = _type_info.data[166];
_type_info.data[19]->interfaces.data[8] = _type_info.data[163];
_type_info.data[19]->methods.data = malloc(35 * sizeof(Type));
_type_info.data[19]->methods.length = 35;
_type_info.data[19]->methods.capacity = 35;
_type_info.data[19]->methods.data[0].$0 = (str){.data="as_byte_slice", .length= 13};
_type_info.data[19]->methods.data[0].$1 = String$as_byte_slice;
_type_info.data[19]->methods.data[1].$0 = (str){.data="as_char_slice", .length= 13};
_type_info.data[19]->methods.data[1].$1 = String$as_char_slice;
_type_info.data[19]->methods.data[2].$0 = (str){.data="iter_mut", .length= 8};
_type_info.data[19]->methods.data[2].$1 = String$iter_mut;
_type_info.data[19]->methods.data[3].$0 = (str){.data="iter", .length= 4};
_type_info.data[19]->methods.data[3].$1 = String$iter;
_type_info.data[19]->methods.data[4].$0 = (str){.data="eq", .length= 2};
_type_info.data[19]->methods.data[4].$1 = String$eq;
_type_info.data[19]->methods.data[5].$0 = (str){.data="chars", .length= 5};
_type_info.data[19]->methods.data[5].$1 = String$chars;
_type_info.data[19]->methods.data[6].$0 = (str){.data="slice_mut", .length= 9};
_type_info.data[19]->methods.data[6].$1 = String$slice_mut;
_type_info.data[19]->methods.data[7].$0 = (str){.data="as_str", .length= 6};
_type_info.data[19]->methods.data[7].$1 = String$as_str;
_type_info.data[19]->methods.data[8].$0 = (str){.data="slice", .length= 5};
_type_info.data[19]->methods.data[8].$1 = String$slice;
_type_info.data[19]->methods.data[9].$0 = (str){.data="clone", .length= 5};
_type_info.data[19]->methods.data[9].$1 = String$clone;
_type_info.data[19]->methods.data[10].$0 = (str){.data="pop", .length= 3};
_type_info.data[19]->methods.data[10].$1 = String$pop;
_type_info.data[19]->methods.data[11].$0 = (str){.data="is_empty_or_whitespace", .length= 22};
_type_info.data[19]->methods.data[11].$1 = String$is_empty_or_whitespace;
_type_info.data[19]->methods.data[12].$0 = (str){.data="is_empty", .length= 8};
_type_info.data[19]->methods.data[12].$1 = String$is_empty;
_type_info.data[19]->methods.data[13].$0 = (str){.data="hash", .length= 4};
_type_info.data[19]->methods.data[13].$1 = String$hash;
_type_info.data[19]->methods.data[14].$0 = (str){.data="subscript_mut", .length= 13};
_type_info.data[19]->methods.data[14].$1 = String$subscript_mut;
_type_info.data[19]->methods.data[15].$0 = (str){.data="back", .length= 4};
_type_info.data[19]->methods.data[15].$1 = String$back;
_type_info.data[19]->methods.data[16].$0 = (str){.data="insert_at", .length= 9};
_type_info.data[19]->methods.data[16].$1 = String$insert_at;
_type_info.data[19]->methods.data[17].$0 = (str){.data="resize", .length= 6};
_type_info.data[19]->methods.data[17].$1 = String$resize;
_type_info.data[19]->methods.data[18].$0 = (str){.data="neq", .length= 3};
_type_info.data[19]->methods.data[18].$1 = String$neq;
_type_info.data[19]->methods.data[19].$0 = (str){.data="push", .length= 4};
_type_info.data[19]->methods.data[19].$1 = String$push;
_type_info.data[19]->methods.data[20].$0 = (str){.data="subscript", .length= 9};
_type_info.data[19]->methods.data[20].$1 = String$subscript;
_type_info.data[19]->methods.data[21].$0 = (str){.data="pop_front", .length= 9};
_type_info.data[19]->methods.data[21].$1 = String$pop_front;
_type_info.data[19]->methods.data[22].$0 = (str){.data="push_front", .length= 10};
_type_info.data[19]->methods.data[22].$1 = String$push_front;
_type_info.data[19]->methods.data[23].$0 = (str){.data="front", .length= 5};
_type_info.data[19]->methods.data[23].$1 = String$front;
_type_info.data[19]->methods.data[24].$0 = (str){.data="substr", .length= 6};
_type_info.data[19]->methods.data[24].$1 = String$substr;
_type_info.data[19]->methods.data[25].$0 = (str){.data="deinit", .length= 6};
_type_info.data[19]->methods.data[25].$1 = String$deinit;
_type_info.data[19]->methods.data[26].$0 = (str){.data="erase_at", .length= 8};
_type_info.data[19]->methods.data[26].$1 = String$erase_at;
;
_type_info.data[12]= malloc(sizeof(Type));
*_type_info.data[12] = (Type){ .id = 12, .name = (str){.data="IsConstPointer", .length = 14}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[12]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[12]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[150]= malloc(sizeof(Type));
*_type_info.data[150] = (Type){ .id = 150, .name = (str){.data="*const u8", .length = 9}, .size = sizeof(void*), .flags = 1024
,
.element_type = _type_info.data[7],
 };{};
{ auto args = &_type_info.data[150]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[150]->interfaces.data = malloc(2 * sizeof(Type));
_type_info.data[150]->interfaces.length = 2;
_type_info.data[150]->interfaces.capacity = 2;
_type_info.data[150]->interfaces.data[0] = _type_info.data[14];
_type_info.data[150]->interfaces.data[1] = _type_info.data[12];
;
{ auto args = &_type_info.data[150]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[18]= malloc(sizeof(Type));
*_type_info.data[18] = (Type){ .id = 18, .name = (str){.data="str", .length = 3}, .size = sizeof(str), .flags = 16
,
.element_type = NULL,
 };_type_info.data[18]->fields.data = malloc(2 * sizeof(Field));
_type_info.data[18]->fields.length = 2;
_type_info.data[18]->fields.capacity = 2;
_type_info.data[18]->fields.data[0] = (Field) { .name = (str){.data="data", .length=4}, .type = _type_info.data[150], .size = sizeof(void*),  };
_type_info.data[18]->fields.data[1] = (Field) { .name = (str){.data="length", .length=6}, .type = _type_info.data[4], .size = sizeof(u64), .offset = offsetof(str, length) };
;
{ auto args = &_type_info.data[18]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[18]->interfaces.data = malloc(7 * sizeof(Type));
_type_info.data[18]->interfaces.length = 7;
_type_info.data[18]->interfaces.capacity = 7;
_type_info.data[18]->interfaces.data[0] = _type_info.data[382];
_type_info.data[18]->interfaces.data[1] = _type_info.data[361];
_type_info.data[18]->interfaces.data[2] = _type_info.data[169];
_type_info.data[18]->interfaces.data[3] = _type_info.data[158];
_type_info.data[18]->interfaces.data[4] = _type_info.data[163];
_type_info.data[18]->interfaces.data[5] = _type_info.data[165];
_type_info.data[18]->interfaces.data[6] = _type_info.data[166];
_type_info.data[18]->methods.data = malloc(17 * sizeof(Type));
_type_info.data[18]->methods.length = 17;
_type_info.data[18]->methods.capacity = 17;
_type_info.data[18]->methods.data[0].$0 = (str){.data="as_byte_slice", .length= 13};
_type_info.data[18]->methods.data[0].$1 = str$as_byte_slice;
_type_info.data[18]->methods.data[1].$0 = (str){.data="as_char_slice", .length= 13};
_type_info.data[18]->methods.data[1].$1 = str$as_char_slice;
_type_info.data[18]->methods.data[2].$0 = (str){.data="neq", .length= 3};
_type_info.data[18]->methods.data[2].$1 = str$neq;
_type_info.data[18]->methods.data[3].$0 = (str){.data="eq", .length= 2};
_type_info.data[18]->methods.data[3].$1 = str$eq;
_type_info.data[18]->methods.data[4].$0 = (str){.data="iter_mut", .length= 8};
_type_info.data[18]->methods.data[4].$1 = str$iter_mut;
_type_info.data[18]->methods.data[5].$0 = (str){.data="iter", .length= 4};
_type_info.data[18]->methods.data[5].$1 = str$iter;
_type_info.data[18]->methods.data[6].$0 = (str){.data="back", .length= 4};
_type_info.data[18]->methods.data[6].$1 = str$back;
_type_info.data[18]->methods.data[7].$0 = (str){.data="subscript", .length= 9};
_type_info.data[18]->methods.data[7].$1 = str$subscript;
_type_info.data[18]->methods.data[8].$0 = (str){.data="is_empty", .length= 8};
_type_info.data[18]->methods.data[8].$1 = str$is_empty;
_type_info.data[18]->methods.data[9].$0 = (str){.data="front", .length= 5};
_type_info.data[18]->methods.data[9].$1 = str$front;
_type_info.data[18]->methods.data[10].$0 = (str){.data="is_empty_or_whitespace", .length= 22};
_type_info.data[18]->methods.data[10].$1 = str$is_empty_or_whitespace;
_type_info.data[18]->methods.data[11].$0 = (str){.data="hash", .length= 4};
_type_info.data[18]->methods.data[11].$1 = str$hash;
_type_info.data[18]->methods.data[12].$0 = (str){.data="slice", .length= 5};
_type_info.data[18]->methods.data[12].$1 = str$slice;
_type_info.data[18]->methods.data[13].$0 = (str){.data="subscript_mut", .length= 13};
_type_info.data[18]->methods.data[13].$1 = str$subscript_mut;
;
_type_info.data[15]= malloc(sizeof(Type));
*_type_info.data[15] = (Type){ .id = 15, .name = (str){.data="IsTuple", .length = 7}, .flags = 8192
,
.element_type = NULL,
 };{};
{ auto args = &_type_info.data[15]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
{ auto args = &_type_info.data[15]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[685]= malloc(sizeof(Type));
*_type_info.data[685] = (Type){ .id = 685, .name = (str){.data="(str)", .length = 5}, .size = sizeof($tuple18), .flags = 128
,
.element_type = NULL,
 };_type_info.data[685]->fields.data = malloc(1 * sizeof(Field));
_type_info.data[685]->fields.length = 1;
_type_info.data[685]->fields.capacity = 1;
_type_info.data[685]->fields.data[0] = (Field) { .name = (str){.data="0", .length=1}, .type = _type_info.data[18], .size = 0, .offset = offsetof($tuple18, $0) };
;
{ auto args = &_type_info.data[685]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[685]->interfaces.data = malloc(1 * sizeof(Type));
_type_info.data[685]->interfaces.length = 1;
_type_info.data[685]->interfaces.capacity = 1;
_type_info.data[685]->interfaces.data[0] = _type_info.data[15];
;
{ auto args = &_type_info.data[685]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[1451]= malloc(sizeof(Type));
*_type_info.data[1451] = (Type){ .id = 1451, .name = (str){.data="(String, u64, u64)", .length = 18}, .size = sizeof($tuple19$4$4), .flags = 128
,
.element_type = NULL,
 };_type_info.data[1451]->fields.data = malloc(3 * sizeof(Field));
_type_info.data[1451]->fields.length = 3;
_type_info.data[1451]->fields.capacity = 3;
_type_info.data[1451]->fields.data[0] = (Field) { .name = (str){.data="0", .length=1}, .type = _type_info.data[19], .size = 0, .offset = offsetof($tuple19$4$4, $0) };
_type_info.data[1451]->fields.data[1] = (Field) { .name = (str){.data="1", .length=1}, .type = _type_info.data[4], .size = sizeof(u64), .offset = offsetof($tuple19$4$4, $1) };
_type_info.data[1451]->fields.data[2] = (Field) { .name = (str){.data="2", .length=1}, .type = _type_info.data[4], .size = sizeof(u64), .offset = offsetof($tuple19$4$4, $2) };
;
{ auto args = &_type_info.data[1451]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[1451]->interfaces.data = malloc(1 * sizeof(Type));
_type_info.data[1451]->interfaces.length = 1;
_type_info.data[1451]->interfaces.capacity = 1;
_type_info.data[1451]->interfaces.data[0] = _type_info.data[15];
;
{ auto args = &_type_info.data[1451]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[371]= malloc(sizeof(Type));
*_type_info.data[371] = (Type){ .id = 371, .name = (str){.data="(u8)", .length = 4}, .size = sizeof($tuple7), .flags = 128
,
.element_type = NULL,
 };_type_info.data[371]->fields.data = malloc(1 * sizeof(Field));
_type_info.data[371]->fields.length = 1;
_type_info.data[371]->fields.capacity = 1;
_type_info.data[371]->fields.data[0] = (Field) { .name = (str){.data="0", .length=1}, .type = _type_info.data[7], .size = sizeof(u8), .offset = offsetof($tuple7, $0) };
;
{ auto args = &_type_info.data[371]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[371]->interfaces.data = malloc(1 * sizeof(Type));
_type_info.data[371]->interfaces.length = 1;
_type_info.data[371]->interfaces.capacity = 1;
_type_info.data[371]->interfaces.data[0] = _type_info.data[15];
;
{ auto args = &_type_info.data[371]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[1075]= malloc(sizeof(Type));
*_type_info.data[1075] = (Type){ .id = 1075, .name = (str){.data="(String)", .length = 8}, .size = sizeof($tuple19), .flags = 128
,
.element_type = NULL,
 };_type_info.data[1075]->fields.data = malloc(1 * sizeof(Field));
_type_info.data[1075]->fields.length = 1;
_type_info.data[1075]->fields.capacity = 1;
_type_info.data[1075]->fields.data[0] = (Field) { .name = (str){.data="0", .length=1}, .type = _type_info.data[19], .size = 0, .offset = offsetof($tuple19, $0) };
;
{ auto args = &_type_info.data[1075]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[1075]->interfaces.data = malloc(1 * sizeof(Type));
_type_info.data[1075]->interfaces.length = 1;
_type_info.data[1075]->interfaces.capacity = 1;
_type_info.data[1075]->interfaces.data[0] = _type_info.data[15];
;
{ auto args = &_type_info.data[1075]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[422]= malloc(sizeof(Type));
*_type_info.data[422] = (Type){ .id = 422, .name = (str){.data="(u32)", .length = 5}, .size = sizeof($tuple5), .flags = 128
,
.element_type = NULL,
 };_type_info.data[422]->fields.data = malloc(1 * sizeof(Field));
_type_info.data[422]->fields.length = 1;
_type_info.data[422]->fields.capacity = 1;
_type_info.data[422]->fields.data[0] = (Field) { .name = (str){.data="0", .length=1}, .type = _type_info.data[5], .size = sizeof(u32), .offset = offsetof($tuple5, $0) };
;
{ auto args = &_type_info.data[422]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[422]->interfaces.data = malloc(1 * sizeof(Type));
_type_info.data[422]->interfaces.length = 1;
_type_info.data[422]->interfaces.capacity = 1;
_type_info.data[422]->interfaces.data[0] = _type_info.data[15];
;
{ auto args = &_type_info.data[422]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[2033]= malloc(sizeof(Type));
*_type_info.data[2033] = (Type){ .id = 2033, .name = (str){.data="(u32, u32)", .length = 10}, .size = sizeof($tuple5$5), .flags = 128
,
.element_type = NULL,
 };_type_info.data[2033]->fields.data = malloc(2 * sizeof(Field));
_type_info.data[2033]->fields.length = 2;
_type_info.data[2033]->fields.capacity = 2;
_type_info.data[2033]->fields.data[0] = (Field) { .name = (str){.data="0", .length=1}, .type = _type_info.data[5], .size = sizeof(u32), .offset = offsetof($tuple5$5, $0) };
_type_info.data[2033]->fields.data[1] = (Field) { .name = (str){.data="1", .length=1}, .type = _type_info.data[5], .size = sizeof(u32), .offset = offsetof($tuple5$5, $1) };
;
{ auto args = &_type_info.data[2033]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[2033]->interfaces.data = malloc(1 * sizeof(Type));
_type_info.data[2033]->interfaces.length = 1;
_type_info.data[2033]->interfaces.capacity = 1;
_type_info.data[2033]->interfaces.data[0] = _type_info.data[15];
;
{ auto args = &_type_info.data[2033]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[446]= malloc(sizeof(Type));
*_type_info.data[446] = (Type){ .id = 446, .name = (str){.data="*const String", .length = 13}, .size = sizeof(void*), .flags = 1040
,
.element_type = _type_info.data[19],
 };{};
{ auto args = &_type_info.data[446]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[446]->interfaces.data = malloc(2 * sizeof(Type));
_type_info.data[446]->interfaces.length = 2;
_type_info.data[446]->interfaces.capacity = 2;
_type_info.data[446]->interfaces.data[0] = _type_info.data[14];
_type_info.data[446]->interfaces.data[1] = _type_info.data[12];
;
{ auto args = &_type_info.data[446]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
_type_info.data[1171]= malloc(sizeof(Type));
*_type_info.data[1171] = (Type){ .id = 1171, .name = (str){.data="Interned!<String>", .length = 17}, .size = sizeof(interned$Interned$19), .flags = 16
,
.element_type = NULL,
 };_type_info.data[1171]->fields.data = malloc(1 * sizeof(Field));
_type_info.data[1171]->fields.length = 1;
_type_info.data[1171]->fields.capacity = 1;
_type_info.data[1171]->fields.data[0] = (Field) { .name = (str){.data="data", .length=4}, .type = _type_info.data[446], .size = sizeof(void*),  };
_type_info.data[1171]->generic_args.data = malloc(1 * sizeof(Type));
_type_info.data[1171]->generic_args.length = 1;
_type_info.data[1171]->generic_args.capacity = 1;
_type_info.data[1171]->generic_args.data[0] = _type_info.data[19];
_type_info.data[1171]->interfaces.data = malloc(3 * sizeof(Type));
_type_info.data[1171]->interfaces.length = 3;
_type_info.data[1171]->interfaces.capacity = 3;
_type_info.data[1171]->interfaces.data[0] = _type_info.data[158];
_type_info.data[1171]->interfaces.data[1] = _type_info.data[163];
_type_info.data[1171]->interfaces.data[2] = _type_info.data[764];
_type_info.data[1171]->methods.data = malloc(6 * sizeof(Type));
_type_info.data[1171]->methods.length = 6;
_type_info.data[1171]->methods.capacity = 6;
_type_info.data[1171]->methods.data[0].$0 = (str){.data="format", .length= 6};
_type_info.data[1171]->methods.data[0].$1 = interned$Interned$19$format;
_type_info.data[1171]->methods.data[1].$0 = (str){.data="hash", .length= 4};
_type_info.data[1171]->methods.data[1].$1 = interned$Interned$19$hash;
_type_info.data[1171]->methods.data[2].$0 = (str){.data="neq", .length= 3};
_type_info.data[1171]->methods.data[2].$1 = interned$Interned$19$neq;
_type_info.data[1171]->methods.data[3].$0 = (str){.data="eq", .length= 2};
_type_info.data[1171]->methods.data[3].$1 = interned$Interned$19$eq;
_type_info.data[1171]->methods.data[4].$0 = (str){.data="insert_or_set", .length= 13};
_type_info.data[1171]->methods.data[4].$1 = interned$Interned$19$insert_or_set;
_type_info.data[1171]->methods.data[5].$0 = (str){.data="value", .length= 5};
_type_info.data[1171]->methods.data[5].$1 = interned$Interned$19$value;
;
_type_info.data[1458]= malloc(sizeof(Type));
*_type_info.data[1458] = (Type){ .id = 1458, .name = (str){.data="(Interned!<String>)", .length = 19}, .size = sizeof($tuple1171), .flags = 128
,
.element_type = NULL,
 };_type_info.data[1458]->fields.data = malloc(1 * sizeof(Field));
_type_info.data[1458]->fields.length = 1;
_type_info.data[1458]->fields.capacity = 1;
_type_info.data[1458]->fields.data[0] = (Field) { .name = (str){.data="0", .length=1}, .type = _type_info.data[1171], .size = 0, .offset = offsetof($tuple1171, $0) };
;
{ auto args = &_type_info.data[1458]->generic_args;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 }_type_info.data[1458]->interfaces.data = malloc(1 * sizeof(Type));
_type_info.data[1458]->interfaces.length = 1;
_type_info.data[1458]->interfaces.capacity = 1;
_type_info.data[1458]->interfaces.data[0] = _type_info.data[15];
;
{ auto args = &_type_info.data[1458]->interfaces;
args->length = 0;
args->data = NULL
;args->capacity = 0;
 };
;
}

void $deinit_type(Type *type) {
  if (type->methods.length > 0 || type->methods.data != NULL)
    free(type->methods.data);

  if (type->interfaces.length  > 0 || type->interfaces.data != NULL)
    free(type->interfaces.data);

  if (type->fields.length  > 0 || type->fields.data != NULL)
    free(type->fields.data);

  if (type->generic_args.length  > 0 || type->generic_args.data != NULL)
    free(type->generic_args.data);

  free(type);
}
void $deinitialize_reflection_system() {
  $deinit_type(_type_info.data[1458]);
  $deinit_type(_type_info.data[1171]);
  $deinit_type(_type_info.data[2033]);
  $deinit_type(_type_info.data[371]);
  $deinit_type(_type_info.data[1451]);
  $deinit_type(_type_info.data[15]);
  $deinit_type(_type_info.data[18]);
  $deinit_type(_type_info.data[150]);
  $deinit_type(_type_info.data[12]);
  $deinit_type(_type_info.data[19]);
  $deinit_type(_type_info.data[169]);
  $deinit_type(_type_info.data[158]);
  $deinit_type(_type_info.data[161]);
  $deinit_type(_type_info.data[685]);
  $deinit_type(_type_info.data[154]);
  $deinit_type(_type_info.data[382]);
  $deinit_type(_type_info.data[149]);
  $deinit_type(_type_info.data[242]);
  $deinit_type(_type_info.data[6]);
  $deinit_type(_type_info.data[446]);
  $deinit_type(_type_info.data[151]);
  $deinit_type(_type_info.data[764]);
  $deinit_type(_type_info.data[10]);
  $deinit_type(_type_info.data[238]);
  $deinit_type(_type_info.data[2]);
  $deinit_type(_type_info.data[361]);
  $deinit_type(_type_info.data[243]);
  $deinit_type(_type_info.data[7]);
  $deinit_type(_type_info.data[34]);
  $deinit_type(_type_info.data[152]);
  $deinit_type(_type_info.data[163]);
  $deinit_type(_type_info.data[172]);
  $deinit_type(_type_info.data[1075]);
  $deinit_type(_type_info.data[13]);
  $deinit_type(_type_info.data[170]);
  $deinit_type(_type_info.data[14]);
  $deinit_type(_type_info.data[11]);
  $deinit_type(_type_info.data[165]);
  $deinit_type(_type_info.data[166]);
  $deinit_type(_type_info.data[1]);
  $deinit_type(_type_info.data[237]);
  $deinit_type(_type_info.data[0]);
  $deinit_type(_type_info.data[236]);
  $deinit_type(_type_info.data[171]);
  $deinit_type(_type_info.data[422]);
  $deinit_type(_type_info.data[245]);
  $deinit_type(_type_info.data[9]);
  $deinit_type(_type_info.data[5]);
  $deinit_type(_type_info.data[241]);
  $deinit_type(_type_info.data[244]);
  $deinit_type(_type_info.data[8]);
  $deinit_type(_type_info.data[4]);
  $deinit_type(_type_info.data[240]);
  $deinit_type(_type_info.data[239]);
  $deinit_type(_type_info.data[3]);
free(_type_info.data);

}

#ifdef TESTING
  #define __TEST_RUNNER_MAIN\
    for (int i = 0; i < sizeof(tests) / sizeof($ela_test); i++) { $ela_test_run(&tests[i]); }
#else 
  #define __TEST_RUNNER_MAIN\
    __ela_main_();
#endif
  
int main (int argc, char** argv) {
  /* initialize command line args. */
  Env$initialize(argc, argv);
  /* reflection system */
  $initialize_reflection_system();
  /* call user main, or dispatch tests, depending on the build type. */
  __TEST_RUNNER_MAIN;
  /* deinitialize command line args. */
  $deinitialize_reflection_system();
}
