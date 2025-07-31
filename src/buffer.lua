local term = require("lui.term")

local buffer = {}
buffer.front = {}                                                              -- bf
buffer.back = {}                                                               -- bb

buffer.register = function(bb, text, x, y)
    if not bb[y] then
        bb[y] = {}
    end
    bb[y][x] = text
end

buffer.compare = function(bb, bf)
    local changed_cells = {}

    for y, col in pairs(bb) do
        for x, _ in pairs(col) do
            if bb[y][x] ~= (bf[y] and bf[y][x]) then
                table.insert(changed_cells, {x = x, y = y})
            end
        end
    end

    return changed_cells
end

buffer.copy = function(bb, bf, cells)
    for _, cell in ipairs(cells) do
        local x, y = cell["x"], cell["y"]
        bf[y] = bf[y] or {}
        bf[y][x] = bb[y][x]
    end
end

buffer.output = function(bb, cells)
    for _, cell in ipairs(cells) do
        term.move_cursor(cell["x"], cell["y"])
        io.write(bb[cell["y"]][cell["x"]])
    end
    io.flush()
end

buffer.clear = function(b)
    for y in pairs(b) do
        b[y] = nil
    end
end

return buffer