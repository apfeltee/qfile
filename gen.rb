#!/usr/bin/ruby

require "yaml"

=begin
    /* ident for this type. defaults to "application.octet_stream" */
    const char* sident;

    /* mime name. defaults to "data" */
    const char* sname;

    /* mime type. defaults to "application/octet-stream" */
    const char* smime;

    /* offset at which to start looking for $matchbytes. defaults to 0 */
    size_t mbstart;

    /* array of bytes to match. can be NULL */
    size_t mblength;
    const unsigned char* matchbytes;


    /* array of "forbidden" bytes - the opposite of $matchbytes. */
    size_t nolength;
    const unsigned char* noneofbytes;

=end

def do_ary(o, ary)
  if ary != nil then
    o.printf("%d, \"", ary.length)
    ary.each do |b|
      o.printf("\\%o", b)
    end
    o.printf("\"")
  else
    o.printf("0, NULL")
  end
end

begin
  data = YAML.load_file("mime.yaml")
  #pp data
  File.open("types.h", "wb") do |o|
    o.printf("static mimeinfo_t knowntypes[] =\n{\n")
    data.each do |sid, dt|
      sname = dt["name"]
      smime = dt["mime"]
      mbstart = dt["mbstart"] || 0
      next if not sname
      printf("processing %p (%p -> %p) ...\n", sid, sname, smime)
      mbytes = dt["matchbytes"]
      nobytes = dt["noneof"]
      o.printf("    {%p, %p, %p, %d, ", sid, sname, smime, mbstart)
      do_ary(o, mbytes)
      o.printf(", ");
      do_ary(o, nobytes)
      o.printf("},\n");
    end
    o.printf("    {NULL, NULL, NULL, 0, 0, NULL, 0, NULL},\n")
    o.printf("};\n");
  end
end




