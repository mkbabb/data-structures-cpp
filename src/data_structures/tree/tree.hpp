#include "src/data_structures/utils/utils.hpp"

#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <tuple>
#include <vector>

#pragma once

namespace ds { namespace tree {

template<class T>
using List = std::vector<T>;

using namespace ranges;

template<class T>
class TreeNode
{
    int tree_order;
    List<TreeNode<T>> children;
    List<T> values;
    std::optional<TreeNode<T>> parent;

    TreeNode(
        int tree_order,
        std::optional<List<TreeNode<T>>>& children = {},
        std::optional<List<T>>& values = {},
        std::optional<TreeNode<T>>& parent = {})
    {
        this->tree_order = tree_order;
        this->parent = parent;

        this->children = children.value_or({});
        this->values = values.value_or({});

        for (auto child :
             this->children | views::filter([](auto x) { return x.has_value(); })) {
            child.parent = *this;
        }
    }

    auto order() -> int
    {
        return this->values.size();
    }

    auto is_leaf() -> bool
    {
        return this->children.size() == 0;
    }

    auto is_internal() -> bool
    {
        return not(this->is_root() or this->is_leaf());
    }

    auto is_root() -> bool
    {
        return not this->parent.has_value();
    }

    auto is_full() -> bool
    {
        return this->values.size() >= this->tree_order;
    }

    auto is_empty() -> bool
    {
        return this->values.size() == 0;
    }

    auto siblings(int parent_ix) -> std::tuple<TreeNode<T>, TreeNode<T>>
    {
        auto get_child = [&](int ix) -> std::optional<TreeNode<T>> {
            if (this->parent.has_value()) {
                if (ix >= 0 and ix < this->parent.children.size()) {
                    return this->parent.children[ix];
                }
            }
            return {};
        };

        auto left_ix = parent_ix - 1;
        auto right_ix = parent_ix + 1;

        return get_child(left_ix), get_child(right_ix);
    }
};

template<class T, class Comparator = decltype(utils::default_comparator)>
class Tree
{
    int order;
    Comparator comparator;
    TreeNode<T> root;

    Tree(int order, Comparator comparator = utils::default_comparator)
    {
        this->order;
        order;
        this->comparator = comparator;
        this->root = this->create_node(order);
    }

    template<class... Args>
    auto create_node(Args&&... args)
    {
        return TreeNode(std::forward<Args>(args)...);
    }

    template<class Container>
    int tree_bisect(Container&& arr, T&& x, bool left = true, bool negate_found = true)
    {
        return utils::bisect(arr, x, this->comparator, left, negate_found);
    }

    auto find(T input_value) -> std::tuple<int, TreeNode<T>>
    {
        auto node = this->root;

        while (true) {
            if (auto ix = this->tree_bisect(node.values, input_value, true, true); ix) {
                ix = -1 * (ix + 1);
                auto child = node.children[ix];

                if (node.is_leaf() or child) {
                    return {ix, node};
                } else {
                    node = child;
                }
            } else {
                return {ix, node};
            }
        }
    }

    template<class S>
    static auto successor(int ix, TreeNode<S> node)
    {
        if (node.is_leaf()) {
            return node;
        } else {
            auto child = node.children[ix + 1];
            while (not child.is_leaf()) {
                child = child.children[0];
            }
            return child;
        }
    }

    auto remove_node(T input_value) -> std::tuple<int, TreeNode<T>, T>
    {
        auto [value_ix, node] = this->find(input_value);

        if (node.is_leaf()) {
            auto child_ix =
                node.is_root() ? 0 : this->tree_bisect(node.parent.values, input_value);
            auto value = node.values.back();
            node.values.pop_back();

            return {child_ix, node, value};
        } else {
            auto successor = Tree::successor(value_ix, node);
            auto value = successor.values[0];
            auto child_ix = this->tree_bisect(successor.parent, value);
            node.values[value_ix] = value;

            auto s_value = successor[0];
            successor.values.erase(0);

            return {child_ix, successor, s_value};
        }
    }
};

}}