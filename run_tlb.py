from subprocess import call

i = 1
while i <= 2 ** 13:
    call(["./tlb", str(i), "1000"])
    i *= 2