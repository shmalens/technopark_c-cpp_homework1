#include "misc.h"
#include "composition.h"

int gen_sec_multiplier(duration_t duration) {
    return duration.hour * HOUR_MULTIPLIER + duration.min * MIN_MULTIPLIER + duration.sec;
}

