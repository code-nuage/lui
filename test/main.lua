local lui = require("lui")

local x, y = 1, 1
local state = true

function lui.load()
    lui.graphics.clear()
end

function lui.update()
    if lui.keyboard.is_down("w") then
        y = y - 1
    end

    if lui.keyboard.is_down("s") then
        y = y + 1
    end

    if lui.keyboard.is_down("d") then
        x = x + 1
    end

    if lui.keyboard.is_down("a") then
        x = x - 1
    end

    if lui.keyboard.is_down("q") then
        lui.stop()
    end

    if lui.keyboard.is_down("c") then
        state = false
    end
end

function lui.draw()
    local w, h = lui.graphics.get_window_size()

    if state == true then
        lui.graphics.draw(os.date("%H:%M:%S"), 1, 1)
        lui.graphics.draw("Multiline\r\nTest", x, y)
        lui.graphics.draw("Press q to exit", 1, h)
    else
        lui.graphics.clear()
    end
end

lui.run()
