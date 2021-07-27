#include "Cell.h"

nlohmann::json Cell::data() {
    nlohmann::json result;
    result["hasMine"] = hasMine;
    result["activated"] = activated;
    result["hasMine"] = hasFlag;
    result["nearbyMines"] = nearbyMines;
    return result;
}
