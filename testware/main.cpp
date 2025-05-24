#include <gtest/gtest.h>

#include "open_addr_map.hpp"

class OpenAddressMapFixture : public ::testing::Test
{
protected:
    OpenAddressMap<int, int, 15> map;
};

TEST_F(OpenAddressMapFixture, CanInsertAndRetreive)
{
    map[10] = 5;
    ASSERT_EQ(map[10], 5);
}

TEST_F(OpenAddressMapFixture, OccupancyOne)
{
    map[10] = 5;
    ASSERT_EQ(map.occupancy(), 1);
}

TEST_F(OpenAddressMapFixture, OccupancyOneReassign)
{
    map[10] = 10;
    ASSERT_EQ(map.occupancy(), 1);
}

TEST_F(OpenAddressMapFixture, Occupancy)
{
    for (int i = 0; i < map.size(); i++)
    {
        map[i] = i;
        ASSERT_EQ(map.occupancy(), i+1);
    }
}

TEST_F(OpenAddressMapFixture, OccupancyToZero)
{
    map[10] = 5;
    map.remove(10);
    ASSERT_EQ(map.occupancy(), 0);
}

TEST_F(OpenAddressMapFixture, CantDeleteNonExistent)
{
    EXPECT_THROW( map.remove(10) , std::runtime_error);
}

TEST_F(OpenAddressMapFixture, NoInfiniteSearchOnInsert)
{
    for (int i = 0; i < map.size(); i++)
    {
        map[i] = i;
    }
    EXPECT_THROW( map[map.size() + 1] = 0 , std::runtime_error);
}