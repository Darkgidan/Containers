#ifndef SET_TREE_HPP
#define SET_TREE_HPP
#include "utility.hpp"
#include "iterators.hpp"

namespace ft
{
    template <typename T>
    class node
    {
        public:
            T       data;
            node*   parent;
            node*   l_son;
            node*   r_son;
            bool    color;
        public:
            node():data(), parent(NULL), l_son(NULL), r_son(NULL), color(1){}
            node(const T &_data):data(_data), parent(NULL), l_son(NULL), r_son(NULL), color(1){}
            ~node(){}
            node(const node &copy){*this = copy;}
            node &operator=(const node &copy){data=copy.data; parent=copy.parent; l_son=copy.l_son; r_son=copy.r_son; color=copy.color;}
    };

    template <typename T>
    class tree
    {
        public:
            typedef ft::node<T> node;
        protected:
            node *root;
            node *past_begin;
            node *past_end;
        public:
            tree():root(NULL), past_begin(NULL), past_end(NULL)
            {past_begin = new node(); past_end = new node();}
            ~tree(){clear();delete past_begin; delete past_end;}
            tree(const tree &copy):root(NULL), past_begin(NULL), past_end(NULL){*this = copy;}
            tree &operator=(const tree &copy){if(this == &copy)return *this;clear();
            for(node* it = copy.begin(); copy.root && it != copy.fpast_end(); it = next_node(it))insert(it->data);return *this;}
            //find
            void show_status(node* target = NULL)const
			{
                std::cout << "SHOW STATUS\n";
				if (target == NULL)
					target = root;
				std::cout << "data: " << target->data<<", color: "<< target->color;
				if (target->parent)
					std::cout << ", parent: " << target->parent->data;
				else
					std::cout << ", parent: NULL";
				if (target->l_son)
					std::cout << ", left: " << target->l_son->data;
				else
					std::cout << ", left: NULL";
				if (target->r_son)
					std::cout << ", right: " << target->r_son->data;
				else
					std::cout << ", right: NULL";
				std::cout << std::endl;
				if(target->l_son)
					show_status(target->l_son);
				if(target->r_son)
					show_status(target->r_son);
			}
            node *find(const T &target)const
            {
                node *tmp = root;
                while(tmp && tmp != past_begin && tmp != past_end)
                {
                    if(target == tmp->data)
                        return(tmp);
                    if(target > tmp->data)
                        tmp = tmp->r_son;
                    else if(target < tmp->data)
                        tmp = tmp->l_son;
                }
                return(NULL);
            }
            node *next_node(node *_node)const
            {
                node *tmp = _node;
                if(tmp == end())
                    return(past_end);
                else if(tmp->r_son)
                    return(succ_finder(tmp));
                else
                {
                    while(_node->data >= tmp->data)
                        tmp = tmp->parent;
                    return(tmp);
                }
            }
            node *prev_node(node *_node)const
            {
                node *tmp = _node;
                if(tmp == begin())
                    return(past_begin);
                else if(tmp->l_son)
                    return(pred_finder(tmp));
                else
                {
                    while(_node->data <= tmp->data)
                        tmp = tmp->parent;
                    return(tmp);
                }
            }
            node *find_lb(const T &target)const
            {
                node *tmp = root;
                if (begin()->data > target)
                    return past_end;
                while(1)
                {
                    if(tmp->data > target)
                    {
                        if(tmp->l_son)
                            tmp = tmp->l_son;
                        else
                        {
                            while(tmp->data > target)
                                tmp = tmp->parent;
                            return(tmp);
                        }
                    }
                    else if(tmp->data < target)
                    {
                        if(tmp->r_son)
                            tmp = tmp->r_son;
                        else
                            return(tmp);
                    }
                    else
                        return(tmp);
                }
            }
            node *find_ub(const T &target)const
            {
                node *tmp = root;
                if (end()->data < target)
                    return past_end;
                while(1)
                {
                    if(tmp->data > target)
                    {
                        if(tmp->l_son)
                            tmp = tmp->l_son;
                        else
                            return(tmp);
                    }
                    else if(tmp->data < target)
                    {
                        if(tmp->r_son)
                            tmp = tmp->r_son;
                        else
                        {
                            while(tmp->data < target)
                                tmp = tmp->parent;
                            return(tmp);
                        }
                    }
                    else
                    {
                        node *temp = tmp;
                        if(tmp == end())
                            return(past_end);
                        else if(tmp->r_son)
                            return(succ_finder(tmp));
                        else
                        {
                            while(temp->data >= tmp->data)
                                tmp = tmp->parent;
                            return(tmp);
                        }
                    }
                }
            }
            //insert
            node *get_parent(const node *target)const
            {
                if(target)
                    return(target->parent);
                else
                    return(NULL);
            }
            node *get_brother(const node *target)const
            {
                if(target)
                {
                    node *tmp = get_parent(target);
                    if(tmp)
                    {
                        if(target == tmp->l_son)
                            return(tmp->r_son);
                        else
                            return(tmp->l_son);
                    }
                    return(NULL);
                }
                return(NULL);
            } 
            void rotate_recolor(node *t_node)
            {
                node *n_parent;
                node *n_uncle;
                node *n_grandpa;
                n_parent = get_parent(t_node);
                if(n_parent == NULL || n_parent->color == 0)
                    return;
                else
                {
                    n_uncle = get_brother(n_parent);
                    n_grandpa = get_parent(n_parent);
                    if(!n_uncle)
                    {
                        if((t_node != n_parent->r_son && n_parent == n_grandpa->r_son) || (t_node != n_parent->l_son && n_parent == n_grandpa->l_son))
                        {
                            if(t_node == n_parent->r_son)
                            {
                                rot_left(t_node);
                                rot_right(t_node);
                            }
                            else
                            {
                                rot_right(t_node);
                                rot_left(t_node);
                            }
                            t_node->color = 0;
                            n_grandpa->color = 1;
                            n_parent->color = 1;
                        }
                        else if((t_node == n_parent->r_son && n_parent == n_grandpa->r_son) || (t_node == n_parent->l_son && n_parent == n_grandpa->l_son))
                        {
                            if(t_node == n_parent->r_son)
                                rot_left(n_parent);
                            else
                                rot_right(n_parent);
                            t_node->color = 1;
                            n_grandpa->color = 1;
                            n_parent->color = 0;
                            return ;
                        }
                    }
                    else if(n_uncle->color == 0)
                    {
                        if((t_node != n_parent->r_son && n_parent == n_grandpa->r_son) || (t_node != n_parent->l_son && n_parent == n_grandpa->l_son))
                        {
                            if(t_node == n_parent->r_son)
                            {
                                rot_left(t_node);
                                rot_right(t_node);
                            }
                            else
                            {
                                rot_right(t_node);
                                rot_left(t_node);
                            }
                            t_node->color = 0;
                            n_grandpa->color = 1;
                            n_parent->color = 1;
                        }
                        else if((t_node == n_parent->r_son && n_parent == n_grandpa->r_son) || (t_node == n_parent->l_son && n_parent == n_grandpa->l_son))
                        {
                            if(t_node == n_parent->r_son)
                                rot_left(n_parent);
                            else
                                rot_right(n_parent);
                            t_node->color = 1;
                            n_grandpa->color = 1;
                            n_parent->color = 0;
                            return ;
                        }
                    }
                    else//red uncle
                    {
                        n_parent->color = 0;
                        n_uncle->color = 0;
                        if (n_grandpa != root)
                            n_grandpa->color = 1;
                        rotate_recolor(n_grandpa);
                    }
                }
            }
            node *insert(const T &value)
            {
                if(find(value))
                    return(NULL);
                clear_past_nodes();
                node *tmp = new node(value);
                if(!root)
                {
                    tmp->color = 0;
                    root = tmp;       
                    add_past_nodes();
                    return tmp;
                }
                node *supp = root;
                while(supp)
                {
                    if(supp->data > value)
                    {
                        if (supp->l_son == NULL)
                            break;
                        supp = supp->l_son;
                    }
                    else
                    {
                        if (supp->r_son == NULL)
                            break;
                        supp = supp->r_son;
                    }
                }
                if(supp->data > value)
                    supp->l_son = tmp;
                else
                    supp->r_son = tmp;
                tmp->parent = supp;
                if(supp->color == 0)
                {
                    add_past_nodes();
                    return(tmp);
                }
                rotate_recolor(tmp);
                add_past_nodes();
                return(tmp);
            }
            //erase
            node *succ_finder(node *ancestor)const
            {
                node *tmp = ancestor->r_son;
                if(!tmp)
                    return(NULL);
                while(tmp->l_son)
                    tmp = tmp->l_son;
                return(tmp);
            }
            node *pred_finder(node *ancestor)const
            {
                node *tmp = ancestor->l_son;
                if(!tmp)
                    return(NULL);
                while(tmp->r_son)
                    tmp = tmp->r_son;
                return(tmp);
            }
            node *leaf_finder(node *target)
            {
                if(target->l_son == NULL && target->r_son == NULL)
                {
                    if(target == root)
                        return target;
                    if(target->parent->r_son == target)
                        target->parent->r_son=NULL;
                    else if(target->parent->l_son == target)
                        target->parent->l_son=NULL;
                    return target;
                }
                node *tmp = pred_finder(target);
                if(tmp == NULL)
                    tmp = succ_finder(target);
                target->data = tmp->data;
                return (leaf_finder(tmp));
            }
            bool get_color(node *target)
            {
                if(!target)
                    return(0);
                return(target->color);
            }
            void DB_manager(node *target)
            {
                if(target == root)
                    return;
                node *brother = get_brother(target);
                if(brother)
                {
                    //black brotha with black sons
                    if(get_color(brother) == 0 && get_color(brother->l_son) == 0 && get_color(brother->r_son) == 0)
                    {
                        brother->color = 1;
                        if(target->parent->color == 1)
                            target->parent->color = 0;
                        else
                            DB_manager(target->parent);
                    }
                    else if(get_color(brother) == 1)
                    {
                        target->parent->color = 1;
                        brother->color = 0;
                        if(target == target->parent->l_son)
                            rot_left(target->parent);
                        else
                            rot_right(target->parent);
                        DB_manager(target);
                    }
                    else if(get_color(brother) == 0)
                    {
                        //case 5
                        if((target == target->parent->l_son && get_color(brother->l_son) == 1 && get_color(brother->r_son) == 0) || 
                           (target == target->parent->r_son && get_color(brother->r_son) == 1 && get_color(brother->l_son) == 0))
                        {
                            if(target == target->parent->l_son)
                            {
                                brother->color = 1;
                                brother->l_son->color = 0;
                                rot_right(brother);
                                DB_manager(target);
                            }
                            else
                            {
                                brother->color = 1;
                                brother->r_son->color = 0;
                                rot_left(brother);
                                DB_manager(target);
                            }
                        }
                        else if((target == target->parent->l_son && get_color(brother->r_son) == 1) || 
                           (target == target->parent->r_son && get_color(brother->l_son) == 1))
                        {
                            brother->color = target->parent->color;
                            target->parent->color = 0;
                            if (target == target->parent->l_son)
                                brother->r_son->color = 0;
                            if (target == target->parent->r_son)
                                brother->l_son->color = 0;
                            if(target == target->parent->l_son)
                                rot_left(target->parent);
                            else
                                rot_right(target->parent);
                        }
                    }
                }
            }  
            bool erase(const T &value)
            {
                if(!find(value))
                    return(0);
                else
                {
                    clear_past_nodes();
                    node *morituro = leaf_finder(find(value));
                    if(morituro->color == 0)
                        DB_manager(morituro);
                    if (morituro == root)
                        root = NULL;
                    delete morituro;
                    add_past_nodes();
                    return(1);
                }
            }
            //rot_left
            void    rot_left(node *pivot)
            {
                node *parent = pivot->parent;
                node *left = pivot->l_son;

                
                pivot->parent = parent->parent;
                if(pivot->parent && pivot->parent->r_son == parent)
                    pivot->parent->r_son = pivot;
                else if(pivot->parent && pivot->parent->l_son == parent)
                    pivot->parent->l_son = pivot;
                pivot->l_son = parent;
                parent->parent = pivot;
                parent->r_son = left;
                if (left)
                    left->parent = parent;
                if (parent == root)
                    root = pivot;
            }
            //rot_right
            void    rot_right(node *pivot)
            {
                node *parent = pivot->parent;
                node *right = pivot->r_son;

                pivot->parent = parent->parent;
                if(pivot->parent && pivot->parent->r_son == parent)
                    pivot->parent->r_son = pivot;
                else if(pivot->parent && pivot->parent->l_son == parent)
                    pivot->parent->l_son = pivot;

                pivot->r_son = parent;
                parent->parent = pivot;
                parent->l_son = right;
                if(right)
                    right->parent = parent;
                if (parent == root)
                    root = pivot;
            }
            //begin
            node *begin()const
            {
                if (root == NULL)
                    return NULL;
                node *tmp = root;
                while(tmp->l_son && tmp->l_son != past_begin)
                   tmp = tmp->l_son;
                return(tmp);
            }
            //end
            node *end()const
            {
                if (root == NULL)
                    return NULL;
                node *tmp = root;
                
                while(tmp->r_son && tmp->r_son != past_end)
                   tmp = tmp->r_son;
                //std::cout << (root == past_begin) << " " << (root->r_son == past_end) << "\n";
                //if (begin() == past_begin && tmp == past_end)
                //    return (past_begin);
                return(tmp);
            }
            //past_begin
            node *fpast_begin()const{return past_begin;}
            //past_end
            node *fpast_end()const{return past_end;}
            //add_past_nodes
            void add_past_nodes()
            {
                if(!root)
                {
                    root = past_begin;
                    root->r_son = past_end;
                    past_end->parent = past_begin;
                }
                else
                {
                    node *tmp;
                    tmp = begin();
                    tmp->l_son = past_begin;
                    past_begin->parent = tmp;
                    tmp = end();
                    tmp->r_son = past_end;
                    past_end->parent = tmp;
                }
            }
            //clear_past_nodes
            void clear_past_nodes()
            {
                if (!root)
                    return ;
                else if(root == past_begin)
                {   
                    root->r_son = NULL;
                    root = NULL;
                    past_end->parent = NULL;
                }
                else
                {
                    node *tmp;
                    tmp = begin();
                    tmp->l_son = NULL;
                    past_begin->parent = NULL;
                    tmp = end();
                    tmp->r_son = NULL;
                    past_end->parent = NULL;
                }
            }
            //clear
            void    clearHelp(node *target)
            {
                if(target == NULL || target == past_begin || target == past_end)
                    return;
                clearHelp(target->l_son);
                clearHelp(target->r_son);
                delete target;
                target = NULL;
                return;
            }
            void    clear(){clear_past_nodes();clearHelp(root);root = NULL;add_past_nodes();}       
    };
}

#endif