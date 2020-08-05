#!/usr/bin/python

def create_node(val) :
    if not val:
        return None
    return [val, None, None]


def _create_tree(L, input, index):
    if(index == len(input)):
        return
    new_L = []
    for cur_node in L:
        left_child_val  = input[index]
        if left_child_val:
            left_child_node = create_node(left_child_val)
            cur_node[1] = left_child_node
            new_L.append(left_child_node)
        index += 1
        if(index == len(input)):
            return
        right_child_val  = input[index]
        if right_child_val:
            right_child_node = create_node(right_child_val)
            cur_node[2] = right_child_node
            new_L.append(right_child_node)
        index += 1
        if(index == len(input)):
            return
    _create_tree(new_L, input, index)
    

def test_create_tree():
    input = (1, None, 3, 2)
    tree = create_node(input[0])
    tree_nodes_in_one_layer = [tree]
    _create_tree(tree_nodes_in_one_layer, input, 1)
    print(tree)
    return

if __name__ == "__main__":
    test_create_tree()
    
