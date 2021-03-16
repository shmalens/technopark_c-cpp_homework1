#include <stdio.h>
#include "gtest/gtest.h"

#define DATA_PATH "../test/data/comp_ok.txt"
#define INPUT_PATH "../test/data/user_input_ok.txt"
#define WRONG_INPUT_PATH "../test/data/user_input_err1.txt"

#define FIRST_SONG_COMP_NAME "Rick Astley - Never Gonna Give You Up"

extern "C" {
#include "processing.h"
}

TEST(ProcessingTest, DataInput_OK) {
    FILE *fd = fopen(DATA_PATH, "r");
    ASSERT_TRUE(fd);

    FILE *fd_input = fopen(INPUT_PATH, "r");
    ASSERT_TRUE(fd_input);

    playlist_t *tmp = NULL;
    size_t amount = 0;
    size_t duration = 0;
    unsigned int bpm = 0;
    ASSERT_EQ(data_input(fd, fd_input, &tmp, &amount, &duration, &bpm), 0);

    ASSERT_TRUE(tmp);
    ASSERT_EQ(tmp->len, 10);
    ASSERT_TRUE(tmp->compositions);

    ASSERT_EQ(amount, 2);
    ASSERT_EQ(duration, 203);
    ASSERT_EQ(bpm, 100);

    fclose(fd);
    fclose(fd_input);
    delete_playlist(tmp);
}

TEST(ProcessingTest, DataInput_Err) {
    FILE *fd = fopen(DATA_PATH, "r");
    ASSERT_TRUE(fd);

    FILE *fd_input = fopen(WRONG_INPUT_PATH, "r");
    ASSERT_TRUE(fd_input);

    playlist_t *tmp = NULL;
    size_t amount = 0;
    size_t duration = 0;
    unsigned int bpm = 0;

    ASSERT_EQ(data_input(NULL, fd_input, &tmp, &amount, &duration, &bpm), ERROR_READ_DATA);
    ASSERT_EQ(data_input(fd, NULL, &tmp, &amount, &duration, &bpm), ERROR_READ_DATA);
    ASSERT_EQ(data_input(fd, fd_input, &tmp, &amount, &duration, &bpm), ERROR_WRONG_INPUT);

    fclose(fd);
    fclose(fd_input);
}

TEST(ProcessingTest, DataProcessing_OK) {
    FILE *fd = fopen(DATA_PATH, "r");
    ASSERT_TRUE(fd);

    FILE *fd_input = fopen(INPUT_PATH, "r");
    ASSERT_TRUE(fd_input);

    playlist_t *tmp = NULL;
    size_t amount = 0;
    size_t duration = 0;
    unsigned int bpm = 0;
    ASSERT_EQ(data_input(fd, fd_input, &tmp, &amount, &duration, &bpm), 0);

    playlist_t *processed = data_processing(tmp,duration, amount, bpm);
    ASSERT_TRUE(processed);
    ASSERT_EQ(processed->len, amount);

    ASSERT_TRUE(processed->compositions);
    ASSERT_STREQ(processed->compositions[0]->title.title, FIRST_SONG_COMP_NAME);

    delete_playlist(processed);
    delete_playlist(tmp);
    fclose(fd);
    fclose(fd_input);
}

TEST(ProcessingTest, DataProcessing_Err) {
    ASSERT_FALSE(data_processing(NULL, 0, 0, 0));

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
