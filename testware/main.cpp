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
    ASSERT_EQ(map.get_occupancy(), 1);
}


TEST_F(OpenAddressMapFixture, OccupancyToZero)
{
    map[10] = 5;
    map.remove(10);
    ASSERT_EQ(map.get_occupancy(), 0);
}

TEST_F(OpenAddressMapFixture, CantDeleteNonExistent)
{
    ASSERT_FALSE(map.remove(10));
}