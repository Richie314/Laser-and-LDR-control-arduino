#pragma once
template <typename T> inline void ShellSort(T* arr, size_t since, size_t to,
  bool (*compare)(T a, T b) = [](T a, T b) {return (a > b); },
  void (*assign)(T& a, const T& b) = [](T& a, const T& b) { a = b; })
{
  for (size_t gap = (to - since) / 2U; gap > 0; gap /= 2U)
  {
    for (size_t i = gap + since; i < to; i++)
    {
      T temp = arr[i];
      size_t j = i;
      for (; j >= (gap + since) && compare(arr[j - gap], temp); j -= gap)
      {
        assign(arr[j], arr[j - gap]);
      }
      assign(arr[j], temp);
    }
  }
}

template <typename T> inline T Average(const T* arr, size_t start, size_t count) {

    T t = arr[start] / count;
    for (size_t i = 1; i < count; i++) {//Start at 1 since first element was already considered
        t += arr[start + i] / count;
    }
    return t;
}
template <typename T> T Map(T x, T in_min, T in_max, T out_min, T out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}