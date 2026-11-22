/**
 * FpvRenderer.cpp
 */
 
#include <cmath>
#include <vector>

#include "FpvRenderer.hpp"
#include "../model/MazeCell.hpp"
#include "../model/IntersectionsDetector.hpp"

const double K = 25000;

// TODO temporary until real textures rendering

const Pixel PIXEL_CEILING{204, 204, 255, 255};
const Pixel PIXEL_FLOOR{153, 153, 153, 255};
const Pixel PIXEL_WALL{153, 204, 153, 255};
const Pixel PIXEL_PICTURE{204, 102, 153, 255};
const Pixel PIXEL_WINDOW{204, 204, 255, 255};
const Pixel PIXEL_EXIT_DOOR{255, 255, 204, 255};

const Pixel getWallPixel(MazeCellType type) {
	switch(type) {
	case MazeCellType::WALL:
		return PIXEL_WALL;
	case MazeCellType::WINDOW:
		return PIXEL_WINDOW;	
	case MazeCellType::PICTURE:
		return PIXEL_PICTURE;	
	default:
		return PIXEL_EXIT_DOOR;	
	}
}

const Pixel getWallPixel(
	double y,
	double lineHeight,
	double wallTop,
	Intersection &intersection
) {
/*
        const textureY = Math.min(
            TEXTURE_SIZE - 1,
            Math.floor((y - wallTop) * TEXTURE_SIZE / lineHeight)
        )
        return getPixelFromTexture(intersection.cell!.type, intersection.getTextureX(), textureY)
*/
	const MazeCellType type = intersection.getCell()->getType();
	return getWallPixel(type);
}

/*
    getHorizontalPixel = (
        y: number,
        intersection: Intersection,
        textureType: TextureType
    ): Pixel => {
        // 0.5 - we use center of pixel
        const distance = K / (2 * Math.abs(y + 0.5 - this.imageHeight / 2))

        const worldX = this.playerPosition.x + distance * intersection.dx!
        const worldY = this.playerPosition.y + distance * intersection.dy!

        return getPixelFromTexture(textureType, this.toTexture(worldX), this.toTexture(worldY))
    }
    
    toTexture = (n: number) =>
        Math.floor(((n % TEXTURE_SIZE) + TEXTURE_SIZE) % TEXTURE_SIZE)    
*/

const Pixel getFloorPixel(
	double y,
	Intersection &intersection
) { 
//this.getHorizontalPixel(y, intersection, "floor")
	return PIXEL_FLOOR;
}

const Pixel getCeilingPixel(
	double y,
	Intersection &intersection
) { 
// this.getHorizontalPixel(y, intersection, "ceiling")
	return PIXEL_CEILING;	
}

const Pixel getPixel(
        double y,
        double wallTop,
        double wallBottom,
        double lineHeight,
        Intersection &intersection
) {
	if (y < wallTop) {
		return getCeilingPixel(y, intersection);
        } else if (y >= wallBottom) {
		return getFloorPixel(y, intersection);
        } else {
		return PIXEL_WALL;
//		return getWallPixel(y, lineHeight, wallTop, intersection);
        }
}

void FpvRenderer::drawVerticalLine(
	double x,
	Intersection &intersection
) {
	const double lineHeight = K / intersection.getDistance();
	
	const double wallTop = floor((height_ - lineHeight) / 2);
	const double wallBottom = floor((height_ + lineHeight) / 2);
	
        for (int y = 0; y < height_; y++) {
		const Pixel pixel = getPixel(y, wallTop, wallBottom, lineHeight, intersection);
		setPixel(x, y, pixel);
	}	
}



/*
const K = 25_000

export const createFpvImageData = (
    context: CanvasRenderingContext2D,
    imageWidth: number,
    imageHeight: number,
    intersections: Intersection[],
    playerPosition: Point
) => {
    new FpvRenderer(context, imageWidth, imageHeight, intersections, playerPosition).render()
}

class FpvRenderer {

    private readonly imageData: ImageData

    constructor(
        private context: CanvasRenderingContext2D,
        private readonly imageWidth: number,
        private readonly imageHeight: number,
        private readonly intersections: Intersection[],
        private readonly playerPosition: Point
    ) {
        this.imageData = context.createImageData(imageWidth, imageHeight)
    }

    render = () => {
        for (let x = 0; x < this.imageWidth; x++) {
            const index = Math.floor(x * this.intersections.length / this.imageWidth)
            this.drawVerticalLine(x, this.intersections[index])
        }

        this.context.putImageData(this.imageData, 0, 0)
    }

    drawVerticalLine = (
        x: number,
        intersection: Intersection,
    ) => {
        const data = this.imageData.data
        const lineHeight = K / intersection.distance!
        const wallTop = Math.floor((this.imageHeight - lineHeight) / 2)
        const wallBottom = Math.floor((this.imageHeight + lineHeight) / 2)

        for (let y = 0; y < this.imageHeight; y++) {
            const pixel = this.getPixel(y, wallTop, wallBottom, lineHeight, intersection)
            setPixel(data, this.imageWidth, x, y, pixel)
        }
    }

    getPixel = (
        y: number,
        wallTop: number,
        wallBottom: number,
        lineHeight: number,
        intersection: Intersection
    ): Pixel => {
        if (y < wallTop) {
            return this.getCeilingPixel(y, intersection)
        } else if (y >= wallBottom) {
            return this.getFloorPixel(y, intersection)
        } else {
            return this.getWallPixel(y, lineHeight, wallTop, intersection)
        }
    }

    getFloorPixel = (
        y: number,
        intersection: Intersection,
    ): Pixel => this.getHorizontalPixel(y, intersection, "floor")

    getCeilingPixel = (
        y: number,
        intersection: Intersection,
    ): Pixel => this.getHorizontalPixel(y, intersection, "ceiling")

    getHorizontalPixel = (
        y: number,
        intersection: Intersection,
        textureType: TextureType
    ): Pixel => {
        // 0.5 - we use center of pixel
        const distance = K / (2 * Math.abs(y + 0.5 - this.imageHeight / 2))

        const worldX = this.playerPosition.x + distance * intersection.dx!
        const worldY = this.playerPosition.y + distance * intersection.dy!

        return getPixelFromTexture(textureType, this.toTexture(worldX), this.toTexture(worldY))
    }

    toTexture = (n: number) =>
        Math.floor(((n % TEXTURE_SIZE) + TEXTURE_SIZE) % TEXTURE_SIZE)

}
*/




void FpvRenderer::updateFrameBuffer() {
	IntersectionsDetector intersectionsDetector(player_, maze_);
	std::vector<Intersection> intersections = intersectionsDetector.calculate();
	
	for (int x = 0; x < width_; x++) {
		const int index = floor(x * intersections.size() / width_);
		drawVerticalLine(x, intersections[index]);
        }	
}

