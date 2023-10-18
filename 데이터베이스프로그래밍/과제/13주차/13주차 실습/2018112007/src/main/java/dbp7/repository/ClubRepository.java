package dbp7.repository;

import dbp7.entity.Club;  //Club.java 경로
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public class ClubRepository {
    @Autowired
    JdbcTemplate jdbcTemplate;

    // club 테이블 전체 검색
    public List<Club> getAllClubs(){
        List<Club> clubs = jdbcTemplate.query("select id, name, category from club",
                (result, rowNum)->new Club(result.getInt("id"), result.getString("name"),
                 result.getString("category")));
        return clubs;
    }

    //id로 검색
    public Optional<Club> getClub(int id) {
        List<Club> result = jdbcTemplate.query("select * from club where id = ?", clubRowMapper(), id);
        return result.stream().findAny();
    }

    //데이터 삽입
    public int addClub(int id, String name, String category){
        String query = "insert into club values(?,?,?)";
        return jdbcTemplate.update(query,id,name,category);
    }

    //데이터 삭제
    public int deleteClub(int id){
        String query = "delete from club where id =?";
        return jdbcTemplate.update(query,id);
    }

    private RowMapper<Club> clubRowMapper() {
        return (rs, rowNum) -> {
            Club club = new Club();
            club.setId(rs.getInt("id"));
            club.setName(rs.getString("name"));
            club.setCategory(rs.getString("category"));
            return club;
        };
    }
}


