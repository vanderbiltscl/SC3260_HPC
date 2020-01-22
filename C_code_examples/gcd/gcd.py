def find_gcd(a, b):
  while True:
    if a > b:
      a = a - b
    elif a < b:
      b = b - a
    else:
      return a
