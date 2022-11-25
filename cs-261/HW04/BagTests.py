#########################################################################################
# Here are some basic tests to make sure your Bag implementation runs correctly
# You can run them by running 'python BagTests.py' from the command line
#########################################################################################

from Bag import *

bag = Bag()

print "Checking basic variable initializations..."
assert bag.size() == 0;
assert bag.is_empty() == 1;


bag.print_bag()
print "done\n"

###################################

print "Checking add, contains, functions..."

bag.add(100)
bag.add(50)
bag.add(150)
bag.add(30)
bag.add(70)
bag.add(700)
bag.add(10)
bag.add(600)
bag.add(600)

assert bag.contains(50) == True
assert bag.contains(600) == True
assert bag.size() == 8

bag.print_bag()
print "done\n"

###################################

print "Checking remove, function(s)..."

bag.remove(50)

bag.print_bag()

bag.remove(150)

assert bag.contains(50) == False
assert bag.contains(150) == False

bag.print_bag()
print "done\n"

###################################

print "Checking that all of the above didn't break things"


bag.add(130)
bag.add(150)
bag.add(140)

assert bag.contains(130) == 1
assert bag.contains(140) == 1
assert bag.contains(150) == 1

bag.print_bag()

bag.remove(70)
bag.remove(130)

bag.print_bag()
print "All checks passed"
