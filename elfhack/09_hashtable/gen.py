n=100000

with open("foo.c", "w") as f:
  for i in range (0, n):
    l = "void foo_" + str(i).zfill(8) + "(void){;}\n"
    f.write(l)
with open("main.c", "w") as f:
  for i in range (0, n):
    l = "void foo_" + str(i).zfill(8) + "(void);\n"
    f.write(l)
  f.write("int main(void) {\n")
  for i in range (0, n):
    l = "void foo_" + str(i).zfill(8) + "();\n"
    f.write(l)
  f.write("return 0;\n")
  f.write("}\n")
