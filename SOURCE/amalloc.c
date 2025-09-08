#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <auxmem.h>
#include <auxmem/heap.h>
#include "private.h"

#define SIZE(thenode) (((node_t *)thenode)->RBound - ((node_t*)thenode)->LBound + 1) 

typedef struct node_t {
	size_t LBound;
	size_t RBound;
	bool used;

	struct node_t * LNode;
	struct node_t * RNode;
} node_t;

static size_t  _alloc(node_t * theNode, size_t size);
static void _free(node_t * theNode, size_t address);
static size_t  _getfree(node_t theNode);
static bool _isempty(node_t theNode);
static void _clean(node_t theNode);
static void _cleansize_ternal(node_t * theNode);

// INTERNALS
size_t _alloc(node_t * theNode, size_t size) {
	if(theNode->used) return 0;
	if(size > SIZE(theNode)) {
		return 0;
	}
	if(size == theNode->RBound - theNode->LBound + 1 && theNode->LNode == NULL) {
		theNode->used = true;
		return theNode->LBound;
	}
	if(theNode->LNode == NULL) {
		theNode->LNode = malloc(sizeof(node_t));
		theNode->RNode = malloc(sizeof(node_t));
		*(theNode->LNode) = (node_t) {theNode->LBound, theNode->LBound + size - 1, true, NULL, NULL};
		*(theNode->RNode) = (node_t) {theNode->LBound + size, theNode->RBound, false, NULL, NULL};
		return theNode->LBound;
	}
	if(!theNode->LNode->used) {
		return _alloc(theNode->LNode, size);
	}
	if(!theNode->RNode->used) {
		size_t out = _alloc(theNode->RNode, size);
		if(theNode->LNode->used && theNode->RNode->used) {
			theNode->used = true;
		}
		return out;
	}
	theNode->used = true;
	return 0;
}

void _free(node_t * theNode, size_t address) {
	if(theNode->LBound == address) {
		theNode->used = false;
		if(theNode->LNode) {
			_free(theNode->LNode, address);
		}
		return;
	}
	if(theNode->RNode) {
		theNode->used = false;
		_free(theNode->RNode, address);
		return;
	}
}

size_t _getfree(node_t theNode) {
	if(!theNode.LNode && !theNode.RNode) return theNode.used ? 0 : SIZE(&theNode);
	else {
		size_t sum = 0;
		if(!theNode.LNode->used) sum += _getfree(*theNode.LNode);
		if(!theNode.RNode->used) sum += _getfree(*theNode.RNode);
		return sum;
	}
}

bool _isempty(node_t theNode) {
	if(theNode.used)
		return false;
	if(!theNode.LNode && !theNode.RNode)
		return true;
	return _isempty(*theNode.LNode) && _isempty(*theNode.RNode);
}

void _clean(node_t theNode) {
	if(theNode.LNode && theNode.RNode) {
		_cleansize_ternal(theNode.LNode);
		_cleansize_ternal(theNode.RNode);
	}
}

void _cleansize_ternal(node_t * theNode) {
	if(theNode->used)
		return;
	if(!theNode->LNode && !theNode->RNode) {
		free(theNode);
		return;
	}
	if(_isempty(*theNode)) {
		_cleansize_ternal(theNode->LNode);
		_cleansize_ternal(theNode->RNode);
		free(theNode);
		return;
	}
}

// EXTERNALS

static node_t top_node_g;

void AMALLOC_init() {
	/* The entire range+ of the Virtual Memory is given to the heap allocator
	 * + We reserve the first byte to act as our NULL value
	 */
	top_node_g = (struct node_t){1, size_g-1, false, NULL, NULL};
}

AM_addr_t AMALLOC_alloc(size_t size) {
	return _alloc(&top_node_g, size);
}

void AMALLOC_free(AM_addr_t address) {
	_free(&top_node_g, address);
}

void AMALLOC_clean() {
	_clean(top_node_g);
}

size_t AMALLOC_getfree() {
	return _getfree(top_node_g);
}

bool AMALLOC_isempty() {
	return _isempty(top_node_g);
}


