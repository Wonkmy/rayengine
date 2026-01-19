game = {}
local tImg = nil
local px = 0
function game.load()
	tImg = graphics.createTexture("test.png")
end

function game.update()
	px = px + 1
end

function game.draw()
	graphics.drawTexture(tImg,px,100)
end

function game.dispose()
	graphics.disposeTexture(tImg)
end

return game