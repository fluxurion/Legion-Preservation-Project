/*
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITY_CONTAINERS_H
#define TRINITY_CONTAINERS_H

#include "Define.h"
#include "Random.h"
#include <algorithm>
#include <utility>
#include <vector>
#include "IteratorPair.h"

namespace Trinity
{
    template<class T>
    constexpr T* AddressOrSelf(T* ptr)
    {
        return ptr;
    }

    template<class T>
    constexpr T* AddressOrSelf(T& not_ptr)
    {
        return std::addressof(not_ptr);
    }

    namespace Containers
    {
        // replace with std::size in C++17
        template<class C>
        constexpr std::size_t Size(C const& container)
        {
            return container.size();
        }

        template<class T, std::size_t size>
        constexpr std::size_t Size(T const(&)[size]) noexcept
        {
            return size;
        }

        template<class C>
        void RandomResizeList(C& container, std::size_t requestedSize)
        {
            uint32 currentSize = uint32(Size(container));
            while (currentSize > requestedSize)
            {
                auto itr = std::begin(container);
                std::advance(itr, urand(0, currentSize - 1));
                container.erase(itr);
                --currentSize;
            }
        }

        template<class C, class Predicate>
        void RandomResizeList(C& container, Predicate&& predicate, std::size_t requestedSize)
        {
            //! First use predicate filter
            C containerCopy;

            if (requestedSize)
            {
                std::copy_if(std::begin(container), std::end(container), std::inserter(containerCopy, std::end(containerCopy)), predicate);
                RandomResizeList(containerCopy, requestedSize);
            }

            container = std::move(containerCopy);
        }

        /*
         * Select a random element from a container.
         *
         * Note: container cannot be empty
         */
        template<class C>
        auto SelectRandomContainerElement(C const& container) -> typename std::add_const<decltype(*std::begin(container))>::type&
        {
            auto it = std::begin(container);
            std::advance(it, urand(0, uint32(Size(container)) - 1));
            return *it;
        }

        /**
         * Select a random element from a container where each element has a different chance to be selected.
         *
         * @param container Container to select an element from
         * @param weights Chances of each element to be selected, must be in the same order as elements in container.
         *                Caller is responsible for checking that sum of all weights is greater than 0.
         *
         * Note: container cannot be empty
        */
        template<class C>
        auto SelectRandomWeightedContainerElement(C const& container, std::vector<double> weights) -> decltype(std::begin(container))
        {
            auto it = std::begin(container);
            std::advance(it, urandweighted(weights.size(), weights.data()));
            return it;
        }

        /**
         * Select a random element from a container where each element has a different chance to be selected.
         *
         * @param container Container to select an element from
         * @param weightExtractor Function retrieving chance of each element in container, expected to take an element of the container and returning a double
         *
         * Note: container cannot be empty
        */
        template<class C, class Fn>
        auto SelectRandomWeightedContainerElement(C const& container, Fn weightExtractor) -> decltype(std::begin(container))
        {
            std::vector<double> weights;
            weights.reserve(Size(container));
            double weightSum = 0.0;
            for (auto& val : container)
            {
                double weight = weightExtractor(val);
                weights.push_back(weight);
                weightSum += weight;
            }
            if (weightSum <= 0.0)
                weights.assign(Size(container), 1.0);

            return SelectRandomWeightedContainerElement(container, weights);
        }

        /**
         * @fn void Trinity::Containers::RandomShuffle(C& container)
         *
         * @brief Reorder the elements of the container randomly.
         *
         * @param container Container to reorder
        */
        template<class C>
        void RandomShuffle(C& container)
        {
            std::shuffle(std::begin(container), std::end(container), RandomEngine::Instance());
        }

        /**
         * @fn void Trinity::Containers::RandomShuffleList(C& container)
         *
         * @brief Reorder the elements of the container randomly.
         *
         * @param container Container to reorder
        */
        template <typename T>
        void RandomShuffleList(std::list<T>& list)
        {
            // create a vector of (wrapped) references to elements in the list
            // http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper
            std::vector<std::reference_wrapper<const T>> vec(list.begin(), list.end());
        
            // shuffle (the references in) the vector
            std::shuffle(vec.begin(), vec.end(), RandomEngine::Instance());
        
            // copy the shuffled sequence into a new list
            std::list<T> shuffled_list { vec.begin(), vec.end() };
        
            // swap the old list with the shuffled list
            list.swap(shuffled_list);
        }
        /**
         * @fn bool Trinity::Containers::Intersects(Iterator first1, Iterator last1, Iterator first2, Iterator last2)
         *
         * @brief Checks if two SORTED containers have a common element
         *
         * @param first1 Iterator pointing to start of the first container
         * @param last1 Iterator pointing to end of the first container
         * @param first2 Iterator pointing to start of the second container
         * @param last2 Iterator pointing to end of the second container
         *
         * @return true if containers have a common element, false otherwise.
        */
        template<class Iterator1, class Iterator2>
        bool Intersects(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
        {
            while (first1 != last1 && first2 != last2)
            {
                if (*first1 < *first2)
                    ++first1;
                else if (*first2 < *first1)
                    ++first2;
                else
                    return true;
            }

            return false;
        }

        /**
         * Returns a pointer to mapped value (or the value itself if map stores pointers)
         */
        template<class M>
        auto MapGetValuePtr(M& map, typename M::key_type const& key) -> decltype(AddressOrSelf(map.find(key)->second))
        {
            if (map.empty())
                return nullptr;

            auto itr = map.find(key);
            return itr != map.end() ? AddressOrSelf(itr->second) : nullptr;
        }
    }
    //! namespace Containers
}
//! namespace Trinity

#endif //! #ifdef TRINITY_CONTAINERS_H
