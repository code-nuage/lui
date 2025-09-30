local term = require("lui.term")

local luierr = function(err)
    local w, h = term.get_size()

    io.write("\27[41m")

    for y = 0, h do
        term.move_cursor(0, y)
        io.write(string.rep(" ", w))
    end

    term.move_cursor(2, 2)
    io.write("ERROR")
    term.move_cursor(2, h - 1)
    io.write("Press anything to exit.")

    local err_w = #err
    term.move_cursor(w / 2 - err_w / 2, h / 2)
    io.write(err)
    io.flush()

    local _ = io.read(1)

    while not _ do
        _  = io.read(1)
        io.write("\27[0m")
        break
    end
end

return luierr