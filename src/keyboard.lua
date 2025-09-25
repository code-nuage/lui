local unistd = require("posix.unistd")
local unistd_fd = unistd.STDIN_FILENO

local keyboard = {
    pressed = {}
}

keyboard.poll = function()
    while true do
        local c = unistd.read(unistd_fd, 1)
        if not c then break end
        keyboard.pressed[c] = true
    end
end

keyboard.is_down = function(key)
    return keyboard.pressed[key] == true
end

keyboard.clear = function()
    keyboard.pressed = {}
end

return keyboard
