#include <stdio.h>
#include "gtest/gtest.h"

#define DATA_PATH_OK "../test/data/comp_ok.txt"
#define DATA_PATH_ERR "../test/data/comp_err.txt"

#define TEST_LEN 2
#define TEST_DURATION 203
#define TEST_BPM 100
#define USER_INPUT_OK_PATH "../test/data/user_input_ok.txt"
#define USER_INPUT_ERR1_PATH "../test/data/user_input_err1.txt"
#define USER_INPUT_ERR2_PATH "../test/data/user_input_err2.txt"
#define USER_INPUT_ERR3_PATH "../test/data/user_input_err3.txt"

extern "C" {
#include "dataloader.h"
}

TEST(DataLoader, ReadData_OK) {
    FILE *fd = fopen(DATA_PATH_OK, "r");
    ASSERT_TRUE(fd);

    const int expected_len = 10;
    playlist_t *playlist = read_data(fd);

    ASSERT_TRUE(playlist);
    ASSERT_EQ(playlist->len, expected_len);

    const char first_title[39] = "Pink Floyd - Another brick in the wall";
    const size_t first_duration = 230;
    const unsigned int first_bpm = 130;
    ASSERT_STREQ(playlist->compositions[0]->title.title, first_title);
    ASSERT_EQ(playlist->compositions[0]->duration, first_duration);
    ASSERT_EQ(playlist->compositions[0]->bpm, first_bpm);

    const char last_title[48] = "Red Hot Chilli Peppers - Especially In Michigan";
    const size_t last_duration = 212;
    const unsigned int last_bpm = 98;
    ASSERT_STREQ(playlist->compositions[expected_len - 1]->title.title, last_title);
    ASSERT_EQ(playlist->compositions[expected_len - 1]->duration, last_duration);
    ASSERT_EQ(playlist->compositions[expected_len - 1]->bpm, last_bpm);

    delete_playlist(playlist);
}

TEST(DataLoader, ReadData_Err) {
    FILE *fd = fopen(DATA_PATH_ERR, "r");
    ASSERT_TRUE(fd);

    playlist_t *playlist = read_data(fd);

    ASSERT_FALSE(playlist);
    ASSERT_FALSE(read_data(NULL));
    fclose(fd);
}

TEST(DataLoader, UserInput_OK) {
    FILE *fd = fopen(USER_INPUT_OK_PATH, "r");
    ASSERT_TRUE(fd);

    size_t len;
    size_t duration;
    unsigned int bpm;
    ASSERT_EQ(get_user_input(fd, &len, &duration, &bpm), 0);
    ASSERT_EQ(len, TEST_LEN);
    ASSERT_EQ(duration, TEST_DURATION);
    ASSERT_EQ(bpm, TEST_BPM);
    fclose(fd);
}

TEST(DataLoader, UserInput_Err) {
    size_t len;
    size_t duration;
    unsigned int bpm;
    ASSERT_EQ(get_user_input(NULL, &len, &duration, &bpm), EMPTY_FILE_POINTER);
    ASSERT_EQ(get_user_input(stdin, NULL, &duration, &bpm), EMPTY_LEN_POINTER);
    ASSERT_EQ(get_user_input(stdin, &len, NULL, &bpm), EMPTY_DURATION_POINTER);
    ASSERT_EQ(get_user_input(stdin, &len, &duration, NULL), EMPTY_BPM_POINTER);

    FILE *fd = fopen(USER_INPUT_ERR1_PATH, "r");
    ASSERT_TRUE(fd);
    ASSERT_EQ(get_user_input(fd, &len, &duration, &bpm), WRONG_COMPILATION_LEN);
    fclose(fd);

    fd = fopen(USER_INPUT_ERR2_PATH, "r");
    ASSERT_TRUE(fd);
    ASSERT_EQ(get_user_input(fd, &len, &duration, &bpm), WRONG_DURATION_INPUT);
    fclose(fd);

    fd = fopen(USER_INPUT_ERR3_PATH, "r");
    ASSERT_TRUE(fd);
    ASSERT_EQ(get_user_input(fd, &len, &duration, &bpm), WRONG_BPM_INPUT);
    fclose(fd);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}