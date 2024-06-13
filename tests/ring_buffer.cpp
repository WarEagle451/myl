#include <myl_wip/ring_buffer.hpp>

#include <catch2/catch_all.hpp>
#include <iostream>
using element_type = myl::u32;

#define MYL_TEST_RB_OOOO myl::ring_buffer<element_type> oooo(4)

#define MYL_TEST_RB_OO21 \
myl::ring_buffer<element_type> ooxx(4);\
ooxx.emplace_back(0);\
ooxx.emplace_front(1);\
ooxx.emplace_front(2);\
ooxx.pop_back();

#define MYL_TEST_RB_O12O \
myl::ring_buffer<element_type> oxxo(4);\
oxxo.emplace_back(0);\
oxxo.emplace_back(1);\
oxxo.emplace_back(2);\
oxxo.pop_front();

#define MYL_TEST_RB_12OO \
myl::ring_buffer<element_type> xxoo(4);\
xxoo.emplace_back(1);\
xxoo.emplace_back(2);

#define MYL_TEST_RB_1OO2 \
myl::ring_buffer<element_type> xoox(4);\
xoox.emplace_back(1);\
xoox.emplace_front(2);

#define MYL_TEST_RB_1234 \
myl::ring_buffer<element_type> xxxx(4);\
xxxx.emplace_back(1);\
xxxx.emplace_back(2);\
xxxx.emplace_back(3);\
xxxx.emplace_back(4);

#define MYL_TEST_RB_CHECK(ring_buffer, size_, capacity_, offset_, linear_, empty_, full_)\
    CHECK(ring_buffer.size() == size_);\
    CHECK(ring_buffer.capacity() == capacity_);\
    CHECK(ring_buffer.offset() == offset_);\
    CHECK(ring_buffer.linear() == linear_);\
    CHECK(ring_buffer.empty() == empty_);\
    CHECK(ring_buffer.full() == full_);

TEST_CASE("myl::ring_buffer", "[ring_buffer.hpp]") {
    SECTION("constructor") {
        SECTION("default") {

        }
        SECTION("copy") {
            SECTION("copy") {

            }
            SECTION("allocator") {

            }
        }
        SECTION("move") {
            SECTION("move") {

            }
            SECTION("allocator") {

            }
        }
        SECTION("allocator") {

        }
        SECTION("list") {

        }
        SECTION("capacity") {

        }
        SECTION("count") {

        }
        SECTION("iterator") {

        }
    }
    SECTION("assignment") {
        SECTION("copy") {

        }
        SECTION("move") {

        }
        SECTION("list") {

        }
    }
    SECTION("size") {
        MYL_TEST_RB_OOOO;
        CHECK(oooo.size() == 0);
        MYL_TEST_RB_OO21;
        CHECK(ooxx.size() == 2);
        MYL_TEST_RB_O12O;
        CHECK(oxxo.size() == 2);
        MYL_TEST_RB_12OO;
        CHECK(xxoo.size() == 2);
        MYL_TEST_RB_1OO2;
        CHECK(xoox.size() == 2);
        MYL_TEST_RB_1234;
        CHECK(xxxx.size() == 4);
    }
    SECTION("capacity") {
        myl::ring_buffer<element_type> a;
        CHECK(a.capacity() == 0);
        MYL_TEST_RB_OOOO;
        CHECK(oooo.capacity() == 4);
        MYL_TEST_RB_OO21;
        CHECK(ooxx.capacity() == 4);
        MYL_TEST_RB_O12O;
        CHECK(oxxo.capacity() == 4);
        MYL_TEST_RB_12OO;
        CHECK(xxoo.capacity() == 4);
        MYL_TEST_RB_1OO2;
        CHECK(xoox.capacity() == 4);
        MYL_TEST_RB_1234;
        CHECK(xxxx.capacity() == 4);
    }
    SECTION("offset") {
        MYL_TEST_RB_OOOO;
        CHECK(oooo.offset() == 0);
        MYL_TEST_RB_OO21;
        CHECK(ooxx.offset() == 2);
        MYL_TEST_RB_O12O;
        CHECK(oxxo.offset() == 1);
        MYL_TEST_RB_12OO;
        CHECK(xxoo.offset() == 0);
        MYL_TEST_RB_1OO2;
        CHECK(xoox.offset() == 3);
        MYL_TEST_RB_1234;
        CHECK(xxxx.offset() == 0);
    }
    SECTION("linear") {
        MYL_TEST_RB_OOOO;
        CHECK(oooo.linear());
        MYL_TEST_RB_OO21;
        CHECK(ooxx.linear());
        MYL_TEST_RB_O12O;
        CHECK(oxxo.linear());
        MYL_TEST_RB_12OO;
        CHECK(xxoo.linear());
        MYL_TEST_RB_1OO2;
        CHECK_FALSE(xoox.linear());
        MYL_TEST_RB_1234;
        CHECK(xxxx.linear());
    }
    SECTION("empty") {
        MYL_TEST_RB_OOOO;
        CHECK(oooo.empty());
        MYL_TEST_RB_OO21;
        CHECK_FALSE(ooxx.empty());
        MYL_TEST_RB_O12O;
        CHECK_FALSE(oxxo.empty());
        MYL_TEST_RB_12OO;
        CHECK_FALSE(xxoo.empty());
        MYL_TEST_RB_1OO2;
        CHECK_FALSE(xoox.empty());
        MYL_TEST_RB_1234;
        CHECK_FALSE(xxxx.empty());
    }
    SECTION("full") {
        MYL_TEST_RB_OOOO;
        CHECK_FALSE(oooo.full());
        MYL_TEST_RB_OO21;
        CHECK_FALSE(ooxx.full());
        MYL_TEST_RB_O12O;
        CHECK_FALSE(oxxo.full());
        MYL_TEST_RB_12OO;
        CHECK_FALSE(xxoo.full());
        MYL_TEST_RB_1OO2;
        CHECK_FALSE(xoox.full());
        MYL_TEST_RB_1234;
        CHECK(xxxx.full());
    }
    SECTION("front") {
        SECTION("front") {
            //MYL_TEST_RB_OOOO;
            //CHECK(oooo.front() == 1);
            MYL_TEST_RB_OO21;
            CHECK(ooxx.front() == 2);
            MYL_TEST_RB_O12O;
            CHECK(oxxo.front() == 1);
            MYL_TEST_RB_12OO;
            CHECK(xxoo.front() == 1);
            MYL_TEST_RB_1OO2;
            CHECK(xoox.front() == 2);
            MYL_TEST_RB_1234;
            CHECK(xxxx.front() == 1);
        }
        SECTION("const") {

        }
    }
    SECTION("back") {
        SECTION("back") {
            //MYL_TEST_RB_OOOO;
            //CHECK(oooo.back() == 1);
            MYL_TEST_RB_OO21;
            CHECK(ooxx.back() == 1);
            MYL_TEST_RB_O12O;
            CHECK(oxxo.back() == 2);
            MYL_TEST_RB_12OO;
            CHECK(xxoo.back() == 2);
            MYL_TEST_RB_1OO2;
            CHECK(xoox.back() == 1);
            MYL_TEST_RB_1234;
            CHECK(xxxx.back() == 4);
        }
        SECTION("const") {

        }
    }
    SECTION("at") {
        SECTION("at") {
            MYL_TEST_RB_OO21;
            CHECK(ooxx.at(0) == 2);
            CHECK(ooxx.at(1) == 1);

            MYL_TEST_RB_1234;
            CHECK(xxxx.at(0) == 1);
            CHECK(xxxx.at(1) == 2);
            CHECK(xxxx.at(2) == 3);
            CHECK(xxxx.at(3) == 4);
        }
        SECTION("const") {

        }
    }
    SECTION("[]") {
        SECTION("[]") {
            MYL_TEST_RB_OO21;
            CHECK(ooxx[0] == 2);
            CHECK(ooxx[1] == 1);

            MYL_TEST_RB_1234;
            CHECK(xxxx[0] == 1);
            CHECK(xxxx[1] == 2);
            CHECK(xxxx[2] == 3);
            CHECK(xxxx[3] == 4);
        }
        SECTION("const") {

        }
    }
    SECTION("emplace_front") {
        myl::ring_buffer<myl::u8> rb(2);
        rb.emplace_front(1);
        rb.emplace_front(2);
        rb.emplace_front(3);
        MYL_TEST_RB_CHECK(rb, 2, 2, 0, true, false, true);
        CHECK(rb.data()[0] == 3);
        CHECK(rb.data()[1] == 2);
    }
    SECTION("emplace_back") {
        myl::ring_buffer<myl::u8> rb(2);
        rb.emplace_back(1);
        rb.emplace_back(2);
        rb.emplace_back(3);
        MYL_TEST_RB_CHECK(rb, 2, 2, 1, false, false, true);
        CHECK(rb.data()[0] == 3);
        CHECK(rb.data()[1] == 2);
    }
    SECTION("push_front") {
        SECTION("copy") {

        }
        SECTION("move") {

        }
    }
    SECTION("push_back") {
        SECTION("copy") {

        }
        SECTION("move") {

        }
    }
    SECTION("pop_front") {
        SECTION("single") {

        }
        SECTION("count") {

        }
    }
    SECTION("pop_back") {
        SECTION("single") {

        }
        SECTION("count") {

        }
    }
    SECTION("insert") {
        SECTION("copy") {

        }
        SECTION("move") {

        }
        SECTION("iterator") {

        }
        SECTION("list") {

        }
    }
    SECTION("erase") {
        SECTION("single") {
            myl::ring_buffer<myl::u8> rb1{ 0, 0, 1, 2, 3, 4, 5, 6, 0, 0 };
            rb1.pop_front(2);
            rb1.pop_back(2);

            rb1.erase(myl::ring_buffer<myl::u8>::iterator(rb1.begin().operator->() + 2, &rb1, false));
            CHECK(rb1[0] == 1);
            CHECK(rb1[1] == 2);
            CHECK(rb1[2] == 4);
            CHECK(rb1[3] == 5);
            CHECK(rb1[4] == 6);
            MYL_TEST_RB_CHECK(rb1, 5, 10, 2, true, false, false);

            myl::ring_buffer<myl::u8> rb2{ 4, 5, 6, 0, 0, 0, 0, 1, 2, 3 };
            rb2.rotate(3);
            rb2.pop_front(4);
            rb2.erase(myl::ring_buffer<myl::u8>::iterator(rb2.begin().operator->() + 1, &rb2, false));
            CHECK(rb2[0] == 1);
            CHECK(rb2[1] == 3);
            CHECK(rb2[2] == 4);
            CHECK(rb2[3] == 5);
            CHECK(rb2[4] == 6);
            MYL_TEST_RB_CHECK(rb2, 5, 10, 0, true, false, false);
            
            myl::ring_buffer<myl::u8> rb3{ 4, 5, 6, 0, 0, 0, 0, 1, 2, 3 };
            rb3.rotate(3);
            rb3.pop_front(4);
            rb3.erase(myl::ring_buffer<myl::u8>::iterator(rb3.end().operator->() - 2, &rb3, false));
            CHECK(rb3[0] == 1);
            CHECK(rb3[1] == 2);
            CHECK(rb3[2] == 3);
            CHECK(rb3[3] == 4);
            CHECK(rb3[4] == 6);
            MYL_TEST_RB_CHECK(rb3, 5, 10, 0, true, false, false);
        }
        SECTION("range") {

        }
    }
    SECTION("assign") {
        SECTION("count") {

        }
        SECTION("iterator") {

        }
        SECTION("list") {

        }
    }
    SECTION("clear") {
        MYL_TEST_RB_OO21;
        ooxx.clear();
        MYL_TEST_RB_CHECK(ooxx, 0, 4, 0, true, true, false);

        MYL_TEST_RB_1234;
        xxxx.clear();
        MYL_TEST_RB_CHECK(xxxx, 0, 4, 0, true, true, false);
    }
    SECTION("fill") {
        MYL_TEST_RB_OOOO;
        oooo.fill(7);
        MYL_TEST_RB_CHECK(oooo, 4, 4, 0, true, false, true);
        CHECK(oooo.data()[0] == 7);
        CHECK(oooo.data()[1] == 7);
        CHECK(oooo.data()[2] == 7);
        CHECK(oooo.data()[3] == 7);

        MYL_TEST_RB_OO21;
        ooxx.fill(5);
        MYL_TEST_RB_CHECK(ooxx, 4, 4, 0, true, false, true);
        CHECK(ooxx.data()[0] == 5);
        CHECK(ooxx.data()[1] == 5);
        CHECK(ooxx.data()[2] == 5);
        CHECK(ooxx.data()[3] == 5);
    }
    SECTION("saturate") {
        MYL_TEST_RB_OOOO;
        oooo.saturate(7);
        MYL_TEST_RB_CHECK(oooo, 4, 4, 0, true, false, true);
        CHECK(oooo.data()[0] == 7);
        CHECK(oooo.data()[1] == 7);
        CHECK(oooo.data()[2] == 7);
        CHECK(oooo.data()[3] == 7);

        MYL_TEST_RB_OO21;
        ooxx.saturate(5);
        MYL_TEST_RB_CHECK(ooxx, 4, 4, 2, false, false, true);
        CHECK(ooxx.data()[0] == 5);
        CHECK(ooxx.data()[1] == 5);
        CHECK(ooxx.data()[2] == 2);
        CHECK(ooxx.data()[3] == 1);

        MYL_TEST_RB_1234;
        xxxx.saturate(5);
        MYL_TEST_RB_CHECK(xxxx, 4, 4, 0, true, false, true);
        CHECK(xxxx.data()[0] == 1);
        CHECK(xxxx.data()[1] == 2);
        CHECK(xxxx.data()[2] == 3);
        CHECK(xxxx.data()[3] == 4);
    }
    SECTION("reserve") {
        myl::ring_buffer<myl::u8> rb1;
        rb1.reserve(8);
        MYL_TEST_RB_CHECK(rb1, 0, 8, 0, true, true, false);
        rb1.reserve(5);
        MYL_TEST_RB_CHECK(rb1, 0, 8, 0, true, true, false);

        myl::ring_buffer<myl::u8> rb2{ 0, 1, 2, 3 };
        rb2.reserve(8);
        MYL_TEST_RB_CHECK(rb2, 4, 8, 0, true, false, false);
        CHECK(rb2.data()[0] == 0);
        CHECK(rb2.data()[1] == 1);
        CHECK(rb2.data()[2] == 2);
        CHECK(rb2.data()[3] == 3);
    }
    SECTION("shrink_to_fit") {

    }
    SECTION("resize") {

    }
    SECTION("rotate") {
        SECTION("position") {

        }
        SECTION("offset") {

        }
    }
    SECTION("align") {

    }
}
