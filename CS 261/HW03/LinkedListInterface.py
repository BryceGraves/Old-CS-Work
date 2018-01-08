from ctypes import *

##############################
#   DO NOT TOUCH THIS FILE  #
# This file interfaces your #
#  python and your C code   #
##############################

# cast type for consistency (and flexibility)
TYPE = c_int

# load in the compiled C library
ll_lib = CDLL('./linkedList.so')

# define the linked list struct locally to match that in the C
class LinkedList(Structure):
    pass

LinkedList._fields_ = [
    ("size", TYPE),
    ("firstLink", POINTER(LinkedList)),
    ("lastLink", POINTER(LinkedList))
]

# create a type to reference the linked list as a pointer since the C does it a lot
linked_list = POINTER(LinkedList)

# map types for each function
createLinkedList = ll_lib.createLinkedList
createLinkedList.restype = linked_list

deleteLinkedList = ll_lib.freeLinkedList
deleteLinkedList.argtypes = [linked_list]

isEmptyList = ll_lib.isEmptyList
isEmptyList.argtypes = [linked_list]
isEmptyList.restype = c_int

printList = ll_lib._printList
printList.argtypes = [linked_list]

addFrontList = ll_lib.addFrontList
addFrontList.argtypes = [linked_list, TYPE]

addBackList = ll_lib.addBackList
addBackList.argtypes = [linked_list, TYPE]

frontList = ll_lib.frontList
frontList.argtypes = [linked_list]
frontList.restype = TYPE

backList = ll_lib.backList
backList.argtypes = [linked_list]
backList.restype = TYPE

removeFrontList = ll_lib.removeFrontList
removeFrontList.argtypes = [linked_list]

removeBackList = ll_lib.removeBackList
removeBackList.argtypes = [linked_list]

ll = createLinkedList()
