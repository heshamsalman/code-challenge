import Data.List
import Data.Function

data Slope = Vertical | Horizontal | Sloped Float deriving(Show, Eq)

data Point = Point Float Float deriving(Eq)

instance Show Point where
  show (Point x y) = "Point(" ++ show (round x) ++ ", " ++ show (round y) ++ ")"

data Line = Line { points :: [Point]
                 , slope :: Slope
                 } deriving(Show, Eq)

combinations :: Int -> [a] -> [[a]]
combinations 0 _ = [[]]
combinations n xs = [ xs !! i : x | i <- [0..(length xs)-1]
                                  , x <- combinations (n-1) (drop (i+1) xs) ]

slopeBetween :: Point -> Point -> Slope
slopeBetween (Point x1 y1) (Point x2 y2)
  | x2 == x1 = Vertical
  | y2 == y1 = Horizontal
  | otherwise =  Sloped $ (y2 - y1) / (x2 - x1)

isPointOnLine :: Slope -> Point -> Line -> Bool
isPointOnLine s p Line { points = points, slope = slope } =
  let (pt1:pt2:_) = points
      (Point px py) = p
      (Point x1 y1) = pt1
      (Point x2 y2) = pt2
  in slope == s && case slope of
    Sloped m -> (m * (px - x1) - py + y1) == 0
    Vertical -> x1 == px
    Horizontal -> y1 == py

lineSegmentIntoLine :: [Line] -> [Point] -> [Line]
lineSegmentIntoLine a (pt1:pt2:_) =
  let slope = slopeBetween pt1 pt2
  in case find (isPointOnLine slope pt1) a of
    Just Line { points = points, slope = slope }
      -> let origLine = Line { points = points, slope = slope }
         in (filter (\l -> l /= origLine) a) ++ [Line { points = nub $ points ++ [pt1, pt2], slope = slope }]
    Nothing
      ->  a ++ [Line { points = [pt1, pt2], slope = slope }]

allLineSegments :: [(Int, Int)] -> [[Point]]
allLineSegments pts =
  combinations 2 $
    map (\(x, y) -> Point (fromIntegral(x)) (fromIntegral(y))) pts

comparePointCount :: Line -> Line -> Ordering
comparePointCount Line { points = points1 } Line { points = points2 } =
  compare (length points1) (length points2)

formattedLine :: Line -> [Char]
formattedLine (Line { points = p, slope = s }) =
  let (pt1:_) = p
  in "Point Count: " ++ (show $ length p) ++ " | Slope: "
    ++ (show s) ++ " | Points: " ++ (show p)

lineWithMaxPoints :: [(Int, Int)] -> [Char]
lineWithMaxPoints pts =
  pts
    & allLineSegments
    & foldl lineSegmentIntoLine []
    & maximumBy comparePointCount
    & formattedLine

pts1 = [(1,1),(2,2),(3,3)]
pts2 = [(1,1), (3,2), (5,3), (4,1), (2,3), (1,4)]
horizontalPts = [(1,1), (2,2), (3,1), (4,1), (5, 1), (6,1), (7,1), (2,3), (1,4)]
verticalPts = [(1,1), (2,2), (3,3), (3,1), (1,2), (1,3), (1,4)]
pts = [pts1, pts2, horizontalPts, verticalPts]

main = mapM_ print $ map lineWithMaxPoints pts
