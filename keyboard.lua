local keyboard = {}

function keyboard.is_down(key)
    if lui.input == key then
        return true
    end
end

function keyboard.is_key_down(ansi)
    if lui.input == ansi then
        return true
    end
end

return keyboard