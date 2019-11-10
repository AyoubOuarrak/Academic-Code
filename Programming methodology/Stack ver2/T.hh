#ifndef T_HH_INCLUSION_GUARD
#define T_HH_INCLUSION_GUARD 1

#include <string>

#if 0

typedef std::string T;

#else

class T {
private:
  static const int max_num_objects = 100;
  static int num_current_objects;

  static int next_id();
  static void register_object(int id);
  static void unregister_object(int id);

  int id_;
  std::string s_;

public:
  T();
  T(const T& y);
  T& operator=(const T& y);
  ~T();

  // Conversione implicita.
  T(const char* s);
  friend bool operator==(const T& x, const T& y);
};

#endif

#endif // T_HH_INCLUSION_GUARD
