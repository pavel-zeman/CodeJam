# Same implementation as in C++, but leveraging Python's support of big integers
# https://codingcompetitions.withgoogle.com/codejam/round/0000000000051705/000000000008830b

def gcd(a, b):
  return a if b == 0 else gcd(b, a % b)

t = int(input())
for tt in range(t):
  n, l = input().split()
  n, l = int(n), int(l)
  nums = [int(n) for n in input().split()]
  out = [0] * (l + 1)
  for i in range(len(nums) - 1):
    if nums[i] != nums[i + 1]:
      g = gcd(nums[i], nums[i + 1])
      out[i] = nums[i] // g
      out[i + 1] = g
      for j in range(i - 1, -1, -1):
        out[j] = nums[j] // out[j + 1]
      for j in range(i + 2, l + 1):
        out[j] = nums[j - 1] // out[j - 1]
      break
  
  unq = list(set(out))
  unq.sort()
  m = {}
  pos = 0
  for x in unq:
    m[x] = pos
    pos += 1
  
  outs = ""
  for i in range(l + 1):
    outs += chr(m[out[i]] + 65)
    
  print("Case #%d: %s" % (tt + 1, outs)) 
  
  
      