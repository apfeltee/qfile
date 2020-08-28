static mimeinfo_t knowntypes[] =
{
    {"text.plain", "text file", "text/plain", 0, 0, NULL, 4, "\0\1\2\3"},
    {"image.jpeg", "JPEG image", "image/jpeg", 0, 3, "\377\330\377", 0, NULL},
    {"image.gif", "GIF image", "image/gif", 0, 5, "\107\111\106\70\71", 0, NULL},
    {"image.png", "PNG image", "image/png", 0, 6, "\211\120\116\107\15\12", 0, NULL},
    {"application.x_shockwave_flash", "Macromedia Flash", "application/x-shockwave-flash", 0, 4, "\103\127\123\21", 0, NULL},
    {"application.vnd.microsoft.portable_executable", "PE32 executable", "application/vnd.microsoft.portable-executable", 0, 4, "\115\132\220\0", 0, NULL},
    {"application.x-msdownload", "PE32 executable (DLL)", "application/x-msdownload", 0, 4, "\115\132\170\0", 0, NULL},
    {"application.x_7z_compressed", "7-zip archive", "application/x-7z-compressed", 0, 7, "\67\172\274\257\47\34\0", 0, NULL},
    {"application.x_bzip2", "bzip2 compressed file", "application/x-bzip2", 0, 4, "\102\132\150\71", 0, NULL},
    {"application.x_gzip", "gzip compressed file", "application/x-gzip", 0, 4, "\37\213\10\10", 0, NULL},
    {"application.x_rar", "RAR archive", "application/x-rar", 0, 7, "\122\141\162\41\32\7\0", 0, NULL},
    {"application.x_xz", "XZ compressed file", "application/x-xz", 0, 6, "\375\67\172\130\132\0", 0, NULL},
    {"application.zip", "Zip archive", "application/zip", 0, 5, "\120\113\3\4\24", 0, NULL},
    {"application.pdf", "PDF document", "application/pdf", 0, 5, "\45\120\104\106\55", 0, NULL},
    {"text.rtf", "RTF Rich Text Format document", "text/rtf", 0, 5, "\173\134\162\164\146", 0, NULL},
    {NULL, NULL, NULL, 0, 0, NULL, 0, NULL},
};
