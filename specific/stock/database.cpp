#pragma once

/// Class stock_data

stock_data& stock_data::open ( )
{
    let file_data = file_txt(file_path);

    // Metric.
    let stock_option = vector<string>(file_data[2].expand_tabs(1).unique().strip().split()[2,-1]).each([] (auto& str) { str.encode(std::text_encoding::id::GBK, std::text_encoding::id::UTF8); });
    for ( int i in range(stock_option.size()) )
        option_map[stock_option[i]] = i;

    // Price.
    self.resize(file_data[3,-3].size(), stock_option.size());
    self.date_map.data_handle().resize(self.row());

    int line_num = 0;
    for ( const auto& line in file_data[3,-3] )
    {
        line_num++;
        let parse_line = line.split('\t');

        let date_str   = parse_line[1].split('/');
        let date_val   = date(int(date_str[1]), int(date_str[2]), int(date_str[3]));

        let price_str  = parse_line[2,-1];
        let price_val  = vector(price_str.size(), [&] (int j) { return float(price_str[j]); });

        self[line_num] = price_val;
        self.date_map.data_handle()[line_num] = pair(date_val, line_num);
    }

    return self;
}

const float& stock_data::operator [] ( const time_point& time, const string_view& option ) const
{
    return self[date_map[time]][option_map[option]];
}

const auto stock_data::dates ( ) const
{
    return date_map.keys();
}

const auto stock_data::options ( ) const
{
    return option_map.keys();
}



/// Class database

database::database ( const char* data_directory )
    extends database ( path(data_directory) )
{

}

database::database ( path data_directory )
{
    open(data_directory);
}

database& database::open ( path data_directory )
{
    if ( not is_directory(data_directory) )
        throw file_error("stock database at {} is not a valid directory", data_directory);

    // Count the files to read.
    array files = data_directory.tree()[is_file];
    self.data_handle().resize(files.size());

    // Read the first 1 line of each file.
    let tasks = std::execution::schedule(global_cpu_scheduler)
              | std::execution::bulk(files.size(), [&] (int i)
                  {
                      i++;
                      let stream = file_stream(files[i], file_stream::read_only(true));
                      string stock_name = (views::istream<char>(stream)
                                        | std::views::take_while([] (auto ch) { return ch != '\n'; })
                                        | std::ranges::to<string>())
                                        . encode(std::text_encoding::GBK, std::text_encoding::UTF8)
                                        . split()[2];

                      const_cast<string&>(self.data_handle()[i].key()) = stock_name;
                      self.data_handle()[i].value().file_path = files[i];
                  });
    std::execution::sync_wait(tasks);

    // Sort by stock-name.
    self.data_handle().sort([] (const auto& stock1, const auto& stock2) { return stock1.key() < stock2.key(); });

    return self;
}

const stock_data& database::operator [] ( const string_view& str ) const
{
    auto& query_data = flat_map<string,stock_data>::operator[](str);

    if ( query_data.empty() )
        const_cast<stock_data&>(query_data).open();

    return query_data;
}




