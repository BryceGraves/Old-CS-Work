from ctypes import *
import os

# cast type for consistency (and flexibility)
TYPE = c_int

# load in the compiled C library
bst_lib_name = 'bsT.so'
bst_lib = CDLL(os.getcwd() + os.sep + bst_lib_name)

# define the bst struct locally to match that in the C
class BST(Structure):
    pass
BST._fields_ = [
    ("root", POINTER(BST)),
    ("count", TYPE)
]

# create a type to reference the linked list as a pointer since the C does it a lot
bst = POINTER(BST)

# map types for each function
newBSTree = bst_lib.newBSTree
newBSTree.restype = bst

isEmptyBSTree = bst_lib.isEmptyBSTree
isEmptyBSTree.argtypes = [bst]
isEmptyBSTree.restype = c_int

containsBSTree = bst_lib.containsBSTree
containsBSTree.argtypes = [bst, TYPE]
containsBSTree.restype = c_int

addBSTree = bst_lib.addBSTree
addBSTree.argtypes = [bst, TYPE]
addBSTree.restype = None

sizeBSTree = bst_lib.sizeBSTree
sizeBSTree.argtypes = [bst]
sizeBSTree.restype = c_int

removeBSTree = bst_lib.removeBSTree
removeBSTree.argtypes = [bst, TYPE]
removeBSTree.restype = None

clearBSTree = bst_lib.clearBSTree
clearBSTree.argtypes = [bst]
clearBSTree.restype = None

deleteBSTree = bst_lib.deleteBSTree
deleteBSTree.argtypes = [bst]
deleteBSTree.restype = None

printTree = bst_lib.printTree
printTree.argtypes = [bst]
printTree.restype = None

printTreeDepth = bst_lib.printTreeDepth
printTreeDepth.argtypes = [bst]
printTreeDepth.restype = None
