#include "gtest/gtest.h"

#define TEST_CAPACITY 12

extern "C" {
#include "playlist.h"
}

TEST(PlaylistTest, Create) {
    playlist_t *playlist = create_playlist(TEST_CAPACITY);

    ASSERT_TRUE(playlist);
    ASSERT_EQ(playlist->capacity, TEST_CAPACITY);
    delete_playlist(playlist);
}

TEST(PlaylistTest, Delete) {
    ASSERT_EQ(delete_playlist(NULL), -1);

    playlist_t *playlist = create_playlist(TEST_CAPACITY);
    ASSERT_EQ(delete_playlist(playlist), 0);
}

char test_title[4] = "AAA";
size_t title_len = 4;
size_t duration = 123;
unsigned int bpm = 90;
composition_t comp = {.title = {.title = test_title, .len = title_len}, .duration = duration, .bpm = bpm};

TEST(PlaylistTest, Add_OK) {
    playlist_t *playlist = create_playlist(TEST_CAPACITY);



    ASSERT_EQ(add_composition(playlist, &comp), 0);
    ASSERT_EQ(playlist->len, 1);
}

TEST(PlaylistTest, Add_Err) {
    playlist_t playlist;

    ASSERT_EQ(add_composition(&playlist, NULL), -1);
    ASSERT_EQ(add_composition(NULL, &comp), -1);
    ASSERT_EQ(add_composition(NULL, NULL), -1);
}

TEST(PlaylistTest, Copy_OK) {
    playlist_t *src = create_playlist(0);
    add_composition(src, &comp);

    playlist_t *copy = copy_playlist(src);

    ASSERT_TRUE(copy);
    ASSERT_EQ(src->len, copy->len);
    ASSERT_EQ(src->capacity, copy->capacity);

    ASSERT_STREQ(src->compositions[0]->title.title, copy->compositions[0]->title.title);

    delete_playlist(copy);
    delete_playlist(src);
}

TEST(PlaylistTest, Copy_Err) {
    ASSERT_FALSE(copy_playlist(NULL));
}

TEST(PlaylistTest, Print) {
    playlist_t playlist;
    ASSERT_EQ(print_playlist(stdout, NULL), -1);
    ASSERT_EQ(print_playlist(NULL, &playlist), -1);
    ASSERT_EQ(print_playlist(stdout, &playlist), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}