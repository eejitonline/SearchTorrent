#include "includes/httplib.h"

int main() {
    using namespace httplib;

    Server svr;

    svr.Get("/:search", [](const Request& req, Response& res){
        auto search = req.path_params.at("search");
        res.set_content(search, "text/html");
    });
    svr.listen("0.0.0.0", 8080);
}