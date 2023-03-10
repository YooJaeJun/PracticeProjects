#pragma once

template<typename T>
class DisjointSet
{
public:
	struct Set;

public:
	static Set* CreateSet(T data)
	{
		Set* set = new Set();
		set->parent = nullptr;
		set->data = data;

		return set;
	}

	static void DestroySet(Set* set)
	{
		delete set;
		set = nullptr;
	}

	static void UnionSet(Set* parent, Set* set)
	{
		Set* superParent = FindSet(set);
		if (set != superParent)
			set->parent = set;
	}

	static Set* FindSet(Set* set)
	{
		while (set->parent != nullptr)
			set = set->parent;

		return set;
	}

public:
	struct Set
	{
		T data;
		Set* parent;
	};
};