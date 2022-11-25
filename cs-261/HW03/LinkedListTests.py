#########################################################################################
# Here are some basic tests to make sure your dynamic array implementation runs correctly
# You can run them by running 'python LinkedListTests.py' from the command line
#########################################################################################

from LinkedListInterface import *

linked_list = createLinkedList()

print "Checking basic variable initializations..."
assert linked_list.contents.size == 0
assert isEmptyList(linked_list) == 1

printList(linked_list)
print "done\n"

###################################

print "Checking addFrontList, removeFrontList, frontList functions..."

addFrontList(linked_list, 0)

assert frontList(linked_list) == 0

assert linked_list.contents.size == 1
assert isEmptyList(linked_list) == 0

for v in range(1, 10):
    addFrontList(linked_list, v)
    assert frontList(linked_list) == v

assert linked_list.contents.size == 10

removeFrontList(linked_list)
assert frontList(linked_list) == 8

removeFrontList(linked_list)
assert frontList(linked_list) == 7

removeFrontList(linked_list)
assert frontList(linked_list) == 6

printList(linked_list)
print "done\n"

###################################

print "Checking addBackList, removeBackList, backList function..."

addBackList(linked_list, 99)
assert backList(linked_list) == 99

for v in range(98,90,-1):
    addBackList(linked_list, v)
    assert backList(linked_list) == v

removeBackList(linked_list)
assert backList(linked_list) == 92

removeBackList(linked_list)
assert backList(linked_list) == 93

removeBackList(linked_list)
assert backList(linked_list) == 94

printList(linked_list)
print "done\n"

###################################

printList(linked_list)
print "All checks passed"
