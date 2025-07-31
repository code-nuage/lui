local term = require("lui.term")
local buffer = require("lui.buffer")
local luierr = require("lui.luierr")

local run = function(lui)
    local state, e = term.save_state()

    local ok, res = xpcall(function()
        term.active_raw_mode()
        term.set_nonblocking()

        term.hide_cursor()

        if type(lui.load) == "function" then
            lui.load()
        end
        while lui.STATE == true do
            if type(lui.update) == "function" then
                lui.update()
            end

            if type(lui.draw) == "function" then
                lui.draw()
            end

            local changed_cells = buffer.compare(buffer.back, buffer.front)
            buffer.output(buffer.back, changed_cells)

            buffer.copy(buffer.back, buffer.front, changed_cells)
        end

        term.show_cursor()

        if not e then
            term.restore_state(state)
        else
            lui.graphics.clear()
        end
    end, function(err)
        luierr(err)
        term.show_cursor()
        term.restore_state(state)
    end)
end

return run
