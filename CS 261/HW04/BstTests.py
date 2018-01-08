#########################################################################################
# Here are some basic tests to make sure your BST implementation runs correctly
# You can run them by running 'python BstTests.py' from the command line
#########################################################################################

from BstInterface import *

def print_tree(bst):
    print "v"*150
    printTreeDepth(bst)
    print "^"*150

bst = newBSTree()

print "Checking basic variable initializations..."
assert sizeBSTree(bst) == 0
assert isEmptyBSTree(bst) == 1

print "done\n"

###################################

print "Checking addBSTree, isEmptyBSTree, containsBSTree, functions..."

addBSTree(bst, 100)

assert sizeBSTree(bst) == 1
assert isEmptyBSTree(bst) == 0
assert containsBSTree(bst, 100) == 1

print_tree(bst)

addBSTree(bst, 50)
addBSTree(bst, 40)
addBSTree(bst, 60)

addBSTree(bst, 150)
addBSTree(bst, 160)
addBSTree(bst, 140)
addBSTree(bst, 140) #NOT A TYPO

print sizeBSTree(bst)
print_tree(bst)

assert sizeBSTree(bst) == 7

assert containsBSTree(bst, 100) == 1
assert containsBSTree(bst, 140) == 1
assert containsBSTree(bst, 60) == 1
assert containsBSTree(bst, 123) == 0

print_tree(bst)

print "Checking removeBSTree, function(s)..."

removeBSTree(bst, 50)
removeBSTree(bst, 150)

assert sizeBSTree(bst) == 5

assert containsBSTree(bst, 150) == 0
assert containsBSTree(bst, 50) == 0
assert containsBSTree(bst, 40) == 1
assert containsBSTree(bst, 140) == 1

###################################

print "Checking that all of the above didn't break things"

addBSTree(bst, 120)
addBSTree(bst, 130)
addBSTree(bst, 150)

assert sizeBSTree(bst) == 8

assert containsBSTree(bst, 120) == 1
assert containsBSTree(bst, 130) == 1
assert containsBSTree(bst, 150) == 1

print_tree(bst)
print "All checks passed"
