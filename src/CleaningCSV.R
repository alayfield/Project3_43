library(dplyr)
library(stringr)

## setwd("~/Documents/COP3530/Project3")
dat <- read.csv("csv/tracks_features.csv")

## Removing unecessary data
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

## Write to new CSV
write.csv(dat,file="csv/cleaned_tracks.csv")
