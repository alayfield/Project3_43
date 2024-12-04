library(dplyr)
library(stringr)
library(MASS)

dat <- read.csv("csv/tracks_features.csv")

## Removing unnecessary data
remove <- c("track_number", "disc_number", "explicit", "time_signature", 
            "key", "mode", "release_date", "loudness", "liveness")
dat <- dat[,!(names(dat) %in% remove)]
album_count <- table(dat$album_id)

## Only songs from the 50s onward
dat <- dat[which(dat$year>=1950),]

## Only songs with unique album IDs of 3 or more songs
valid <- names(album_count)[album_count > 3]
dat <- dat[which(dat$album_id %in% valid),]


## Only songs with unique album IDs of 30 minutes or longer
duration <- aggregate(duration_ms ~ album_id, data=dat, sum)
invalid <- duration$album_id[duration$duration_ms < 1800000]
dat <- dat[!dat$album_id %in% invalid,] 
dat <- dat[,!(names(dat) %in% "duration_ms")]

## Remove common compilation albums, Christmas albums, soundtracks, etc.
remove2 <- c("Greatest Hits", "Christmas", "Soundtrack", "Best of", "Compilation", 
             "Broadway", "Music From The Motion Picture", "Gospel", "Anniversary", 
             "Anniversario", "Cast Recording", "Motion Picture Score", "Hymn", 
             "Favorites", "Anniversaire", "Teenbeat Sampler", "for Meditation",
             "Grammy")

for (elem in remove2) {
  dat <- dat[!grepl(elem, dat$album, ignore.case=TRUE),]
}

## Format artist names to only include main artist
subfrom <- c("\"", "\\\\xa0", "\\\\", "^\\['([^']+)'(?:, .*)?\\]$")
subto <- c("'", " ", " ", "\\1")

for (i in 1:4) {
  dat$artists <- gsub(subfrom[i], subto[i], dat$artists)
  dat$artist_ids <- gsub(subfrom[i], subto[i], dat$artist_ids)
}

## Remove compilation albums
albumCount <- count(dat, album_id, artists)
allAlbums <- names(table(albumCount$album_id))

soloAlbum <- allAlbums[table(albumCount$album_id) == 1]
length(soloAlbum)

dat <- dat[which(dat2$album_id %in% soloAlbum),]

## Removed commas in strings
dat$name <- gsub(",", "", dat$name)
dat$album <- gsub(",", "", dat$album)
dat$artists <- gsub(",", "", dat$artists)

## Write to new CSV
write.csv(dat,file="csv/cleaned_tracks.csv")

## Finding inverse covariance matrix
remove <- c("id", "name", "album", "album_id",
            "artists", "artist_ids", "tempo", "year")
dat <- dat[,!(names(dat) %in% remove)]
res <- cov(dat)
res <-ginv(res)

means <- colMeans(dat)
means

write.csv(res, file="csv/cov_matrix.csv")