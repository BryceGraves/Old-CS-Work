#########################################################################################
# Here are some basic tests to make sure your dynamic array implementation runs correctly
# You can run them by running 'python DynamicArrayTests.py' from the command line
#########################################################################################

from DynamicArray import DynamicArray

dyn_arr = DynamicArray()

print "Checking basic variable initializations..."
assert dyn_arr._size == dyn_arr.size()
assert dyn_arr._capacity == dyn_arr.capacity()

dyn_arr.print_data()
print "done\n"

###################################

print "Checking add function..."

dyn_arr.add(1)
assert dyn_arr.size() == 1
assert dyn_arr.capacity() == DynamicArray.INIT_CAPACITY

for v in range(2, dyn_arr.capacity() + 1):
    dyn_arr.add(v)

assert dyn_arr.capacity() == DynamicArray.INIT_CAPACITY

dyn_arr.add(7)

assert dyn_arr.capacity() == DynamicArray.INIT_CAPACITY * DynamicArray.RESIZE_MULTIPLIER

for v in range(dyn_arr.size() + 1, dyn_arr.capacity() + 1):
    dyn_arr.add(v)

dyn_arr.print_data()
print "done\n"

###################################

print "Checking get function..."

for pos in range(dyn_arr.size()):
    assert dyn_arr.get(pos) == pos + 1

dyn_arr.print_data()
print "done\n"

###################################

print "Checking put function..."

for pos in range(dyn_arr.size()):
    dyn_arr.put(pos, pos)

for pos in range(dyn_arr.size()):
    assert dyn_arr.get(pos) == pos

dyn_arr.print_data()
print "done\n"

###################################

print "Checking swap function..."

for pos in range(dyn_arr.size() - 1):
    dyn_arr.swap(pos, pos + 1)

for pos in range(dyn_arr.size()-1):
    assert dyn_arr.get(pos) == pos + 1

assert dyn_arr.get(dyn_arr.size() - 1) == 0

dyn_arr.print_data()
print "done\n"

###################################

print "Checking remove function..."

assert dyn_arr.remove(7) == 8
assert dyn_arr.remove(7) == 9
assert dyn_arr.remove(7) == 10

assert dyn_arr.remove(3) == 4
assert dyn_arr.remove(3) == 5
assert dyn_arr.remove(3) == 6

dyn_arr.print_data()
print "done\n"

###################################

dyn_arr.print_data()
print "All checks passed"