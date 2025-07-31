local keyboard = {}

keyboard.is_down = function(key)
    local input = io.read(1)
    if key == input then
        return true
    end
end

return keyboard